#include <pybind11/pybind11.h>
#include <adi/ADIS16448_IMU.h>

enum SPIPort { kOnboardCS0 = 0, kOnboardCS1 = 1, kOnboardCS2 = 2, kOnboardCS3 = 3, kMXP = 4 }; // Should match values in robotpy-wpilib

PYBIND11_MODULE(ADIS16448, m) {
    m.doc() = "ADIS16448 interface for Python (C++ wrapper)";

    pybind11::class_<frc::ADIS16448_IMU> IMUClass(m, "ADIS16448_IMU");
    IMUClass.def(pybind11::init())
        .def(pybind11::init([](frc::ADIS16448_IMU::IMUAxis initAxis, frc::ADIS16448_IMU::AHRSAlgorithm initAlgo, SPIPort initPort) {
            HAL_SPIPort halPort = HAL_SPIPort::HAL_SPI_kInvalid;

            switch(initPort)
            {
            case SPIPort::kOnboardCS0:
                halPort = HAL_SPIPort::HAL_SPI_kOnboardCS0;
                break;
            case SPIPort::kOnboardCS1:
                halPort = HAL_SPIPort::HAL_SPI_kOnboardCS1;
                break;
            case SPIPort::kOnboardCS2:
                halPort = HAL_SPIPort::HAL_SPI_kOnboardCS2;
                break;
            case SPIPort::kOnboardCS3:
                halPort = HAL_SPIPort::HAL_SPI_kOnboardCS3;
                break;
            case SPIPort::kMXP:
                halPort = HAL_SPIPort::HAL_SPI_kMXP;
                break;
            }

            return new frc::ADIS16448_IMU(initAxis, initAlgo, halPort);
        }))
        .def("Calibrate", &frc::ADIS16448_IMU::Calibrate)
        .def("Reset", &frc::ADIS16448_IMU::Reset)
        .def("GetAngle", &frc::ADIS16448_IMU::GetAngle)
        .def("GetRate", &frc::ADIS16448_IMU::GetRate)
        .def("GetAngleX", &frc::ADIS16448_IMU::GetAngleX)
        .def("GetAngleY", &frc::ADIS16448_IMU::GetAngleY)
        .def("GetAngleZ", &frc::ADIS16448_IMU::GetAngleZ)
        .def("GetRateX", &frc::ADIS16448_IMU::GetRateX)
        .def("GetRateY", &frc::ADIS16448_IMU::GetRateY)
        .def("GetRateZ", &frc::ADIS16448_IMU::GetRateZ)
        .def("GetAccelX", &frc::ADIS16448_IMU::GetAccelX)
        .def("GetAccelY", &frc::ADIS16448_IMU::GetAccelY)
        .def("GetAccelZ", &frc::ADIS16448_IMU::GetAccelZ)
        .def("GetMagX", &frc::ADIS16448_IMU::GetMagX)
        .def("GetMagY", &frc::ADIS16448_IMU::GetMagY)
        .def("GetMagZ", &frc::ADIS16448_IMU::GetMagZ)
        .def("GetPitch", &frc::ADIS16448_IMU::GetPitch)
        .def("GetRoll", &frc::ADIS16448_IMU::GetRoll)
        .def("GetYaw", &frc::ADIS16448_IMU::GetYaw)
        .def("Getdt", &frc::ADIS16448_IMU::Getdt)
        .def("GetStatus", &frc::ADIS16448_IMU::Getdt)
        .def("GetBarometricPressure", &frc::ADIS16448_IMU::GetBarometricPressure)
        .def("GetTemperature", &frc::ADIS16448_IMU::GetTemperature)
        .def("GetQuaternionW", &frc::ADIS16448_IMU::GetQuaternionW)
        .def("GetQuaternionX", &frc::ADIS16448_IMU::GetQuaternionX)
        .def("GetQuaternionY", &frc::ADIS16448_IMU::GetQuaternionY)
        .def("GetQuaternionZ", &frc::ADIS16448_IMU::GetQuaternionZ)
        .def("SetTiltCompYaw", &frc::ADIS16448_IMU::SetTiltCompYaw);
    
    pybind11::enum_<SPIPort>(IMUClass, "SPIPort")
        .value("kOnboardCS0", SPIPort::kOnboardCS0)
        .value("kOnboardCS1", SPIPort::kOnboardCS1)
        .value("kOnboardCS2", SPIPort::kOnboardCS2)
        .value("kOnboardCS3", SPIPort::kOnboardCS3)
        .value("kMXP", SPIPort::kMXP);
    
    pybind11::enum_<frc::ADIS16448_IMU::IMUAxis>(IMUClass, "IMUAxis")
        .value("kX", frc::ADIS16448_IMU::IMUAxis::kX)
        .value("kY", frc::ADIS16448_IMU::IMUAxis::kY)
        .value("kZ", frc::ADIS16448_IMU::IMUAxis::kZ);
    
    pybind11::enum_<frc::ADIS16448_IMU::AHRSAlgorithm>(IMUClass, "AHRSAlgorithm")
        .value("kComplementary", frc::ADIS16448_IMU::AHRSAlgorithm::kComplementary)
        .value("kMadgwick", frc::ADIS16448_IMU::AHRSAlgorithm::kMadgwick);
}