from subprocess import run
from sys import stderr
from os import walk, path

compilerCmd = 'arm-frc2019-linux-gnueabi-g++'

includeDirs = ['./include', './allwpilib/wpiutil/src/main/native/include','./hal_headers',
    './roborio-python/python3.7m', './pybind11/include']

sourceFiles = list()
for (dirpath, dirnames, filenames) in walk('./src'):
    sourceFiles.extend([path.join(dirpath, thisFilePath) for thisFilePath in filenames])

compileArgList = [compilerCmd, '-Wall', '-fPIC', '-D', 'IMU_PY_MODULE']

for thisDir in includeDirs:
    compileArgList.append('-I')
    compileArgList.append(thisDir)

for thisFile in sourceFiles:
    compileArgList.append('-c')
    compileArgList.append(thisFile)

print('Compiling with', compileArgList, '...')
compilationResult = run(compileArgList)

if compilationResult.returncode != 0:
    print('Command exited with code', compilationResult.returncode, '; see output above.', file=stderr)
    exit(compilationResult.returncode)

linkerDirs = ['./hal_libs/linux/athena/shared', './wpiutil_libs/linux/athena/shared']
libNames = ['wpiHal', 'wpiutil']

linkerArgList = [compilerCmd, '-shared', '-fPIC']

for thisDir in linkerDirs:
    linkerArgList.append('-L')
    linkerArgList.append(thisDir)

for thisLib in libNames:
    linkerArgList.append('-l')
    linkerArgList.append(thisLib)

# Files to be linked (generated .o files in current directory)
linkerArgList.extend([path.basename(path.splitext(thisPath)[0]) + '.o' for thisPath in sourceFiles])

linkerArgList.extend(['-o', 'ADIS16448.so'])

print('Linking with', linkerArgList, '...')
linkResult = run(linkerArgList)

if linkResult.returncode != 0:
    print('Command exited with code', linkResult.returncode, '; see output above.', file=stderr)
    exit(linkResult.returncode)

print('Python module built successfully.')