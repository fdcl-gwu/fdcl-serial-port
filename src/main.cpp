#include "fdcl/serial_port.hpp"
#include <unistd.h>


int main(int argc, char **argv)
{
    fdcl::serial_port serial;

    std::string port_name = "/dev/ttyACM0";
    serial.open(port_name);

    int i = 0;
    while (i < 1000)
    {
        char buffer[3];
        // int num_bytes = serial.read(buffer, 3);

        std::cout << serial.read(buffer, 1) << std::endl;;
        int num_bytes;
        if (num_bytes > 0)
        {
            std::cout << atoi(buffer) << std::endl;
        }

        usleep(1000);
        i++;
    }
    serial.close();

    return 0;
}