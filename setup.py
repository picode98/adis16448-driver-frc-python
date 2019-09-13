from shutil import copy

copy('./robotpy-wpilib/hal-roborio/hal_impl/distutils.py', './distutils_renamed.py')

import distutils_renamed

distutils_renamed.extract_hal_headers('./hal_headers')
distutils_renamed.extract_hal_libs('./hal_libs')
distutils_renamed.extract_wpiutil_libs('./wpiutil_libs')