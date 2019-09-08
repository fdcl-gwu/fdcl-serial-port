#include "fdcl/serial_port.hpp"
#include <unistd.h>


int main(int argc, char **argv)
{
    // Open the serial port
    fdcl::serial_port serial;
    std::string port_name = "/dev/ttyACM0";
    serial.open(port_name);

    // Wait two seconds until Arduino starts sending data
    usleep(2000);

    // Clear the incoming buffer
    serial.clear_buffer_until_newline();
    
    // Start reading data 
    int i = 0;
    while (i < 1000)
    {
        // Make sure that this is longer than the size of the array you expect
        // to read.
        int buf_len = 5;  
        char buffer[buf_len];

        int num_bytes = serial.read_line(buffer, buf_len);
        if (num_bytes > 0)
        {
            std::cout << buffer << std::endl;
        }

        usleep(1000);
        i++;
    }
    serial.close();

    return 0;
}