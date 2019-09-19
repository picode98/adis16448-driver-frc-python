# ADIS16448 Driver for FRC Python

**Note:** This project is not yet fully complete. It is not currently advisable to use it in production code.

This repository contains a driver for the Analog Devices ADIS16448 IMU for FRC Python teams. The interface follows (and the implementation is based on) that of [Juan Chong's C++ driver for the official FRC languages](https://github.com/juchong/ADIS16448-RoboRIO-Driver).

## Installation

### roboRIO - Binaries

TBD

### roboRIO - Compiling from source

#### Dependencies

- Requires the FRC 2019 roboRIO cross-compiler (`arm-frc2019-linux-gnueabi-g++`). This is installed with the WPILib C++ tools for FRC teams.

#### Procedure

1. Run the `setup.py` script.
2. Run the `build.py` script.
3. Copy `ADIS16448.so` into the root directory of your robot project. At this point, you should be able to use `import ADIS16448` on the roboRIO.

## Simulation (RobotPy)

TBD

## Functions

See the [C++ class header](include/adi/ADIS16448_IMU.h) for available functions.