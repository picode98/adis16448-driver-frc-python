#include <pybind11/pybind11.h>
#include <adi/ADIS16448_IMU.h>

PYBIND11_MODULE(ADIS16448, m) {
    m.doc() = "ADIS16448 interface for Python (C++ wrapper)"; // optional module docstring

    pybind11::class_<frc::ADIS16448_IMU>(m, "ADIS16448_IMU")
        .def(pybind11::init())
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
}