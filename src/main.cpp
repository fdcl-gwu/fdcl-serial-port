#include "fdcl/serial_port.hpp"

int main(void)
{
    fdcl::serial_port serial;

    std::string port_name = "/dev/ttyACM0";
    serial.open(port_name);

    serial.close();
}