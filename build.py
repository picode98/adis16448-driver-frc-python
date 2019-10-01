from subprocess import run, PIPE
from sys import stderr
from os import walk, path
import re


compilerCmd = 'arm-frc2019-linux-gnueabi-g++'

includeDirs = ['./include', './allwpilib/wpiutil/src/main/native/include', './hal_headers', './allwpilib/wpilibc/src/main/native/include', './allwpilib/ntcore/src/main/native/include'
    , './roborio-python/python3.7m', './pybind11/include']

regexSourceMaps = [(re.compile(regexStr), destPath, nameGroupIndex) for (regexStr, destPath, nameGroupIndex) in [
    (r'allwpilib\/wpilibc\/src\/main\/native\/include\/(frc\/)?(.*?)\.h', './allwpilib/wpilibc/src/main/native/cpp', 1),
    (r'allwpilib\/ntcore\/src\/main\/native\/include\/(.*?)\.h', './allwpilib/ntcore/src/main/native/cpp', -1)]]

def sourceFileExists(filePath):
    fileExists = path.exists(filePath)
    if not(fileExists):
        print('NOTE: File "%s" does not exist. This likely indicates an inline header, but may also have a missing source file.' % filePath)
    return fileExists

baseSourceFiles = set()
for (dirpath, dirnames, filenames) in walk('./src'):
    baseSourceFiles.update([path.join(dirpath, thisFilePath) for thisFilePath in filenames])
oldSourceFiles = baseSourceFiles.copy()
newSourceFiles = set()

baseCompileArgList = [compilerCmd, '-Wall', '-fPIC', '-D', 'IMU_PY_MODULE']

while True:
    preprocessArgList = baseCompileArgList.copy()
    preprocessArgList.extend(['-E', '-H'])

    for thisDir in includeDirs:
        preprocessArgList.append('-I')
        preprocessArgList.append(thisDir)

    for thisFile in oldSourceFiles:
        # compileArgList.extend(['-MT', thisFile])
        preprocessArgList.append('-c')
        preprocessArgList.append(thisFile)

    print('Preprocessing with', preprocessArgList, '...')
    preprocessResult = run(preprocessArgList, stderr=PIPE, stdout=PIPE)
    depsText = preprocessResult.stderr.decode('utf-8')
    # print(depsText)

    newSourceFiles = baseSourceFiles.copy()
    for (thisRegex, thisDest, thisGroupIndex) in regexSourceMaps:
        resultList = thisRegex.findall(depsText)
        thisDepsListPart = list()
        if (thisRegex.groups >= 2):
            thisDepsListPart = [path.join(thisDest, thisName[thisGroupIndex]) + '.cpp' for thisName in resultList]
        else:
            thisDepsListPart = [path.join(thisDest, thisName) + '.cpp' for thisName in resultList]
        thisDepsListPart = filter(sourceFileExists, thisDepsListPart)
        newSourceFiles.update(thisDepsListPart)
        print('Should include:', list(thisDepsListPart))
    
    print('Number of source files:', len(newSourceFiles))
    if len(newSourceFiles) <= len(oldSourceFiles):
        break
    
    oldSourceFiles = newSourceFiles

compileArgList = baseCompileArgList.copy()

for thisDir in includeDirs:
    compileArgList.append('-I')
    compileArgList.append(thisDir)

for thisFile in newSourceFiles:
    compileArgList.append('-c')
    compileArgList.append(thisFile)

print('Compiling with', compileArgList, '...')
compilationResult = run(compileArgList)

if compilationResult.returncode != 0:
    print('Command exited with code', compilationResult.returncode, '; see output above.', file=stderr)
    exit(compilationResult.returncode)

linkerDirs = ['./hal_libs/linux/athena/shared', './wpiutil_libs/linux/athena/shared', './roborio-python']
libNames = ['wpiHal', 'wpiutil', 'python3']

linkerArgList = [compilerCmd, '-shared', '-fPIC', '-Wl,-z,defs']

for thisDir in linkerDirs:
    linkerArgList.append('-L')
    linkerArgList.append(thisDir)

for thisLib in libNames:
    linkerArgList.append('-l')
    linkerArgList.append(thisLib)

# Files to be linked (generated .o files in current directory)
linkerArgList.extend([path.basename(path.splitext(thisPath)[0]) + '.o' for thisPath in newSourceFiles])

linkerArgList.extend(['-o', 'ADIS16448.so'])

print('Linking with', linkerArgList, '...')
linkResult = run(linkerArgList)

if linkResult.returncode != 0:
    print('Command exited with code', linkResult.returncode, '; see output above.', file=stderr)
    exit(linkResult.returncode)

print('Python module built successfully.')