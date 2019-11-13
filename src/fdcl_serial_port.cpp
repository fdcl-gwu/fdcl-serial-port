#include "fdcl/serial_port.hpp"


fdcl::serial_port::serial_port(void)
{
    fdcl::serial_port::init();
}


fdcl::serial_port::serial_port(std::string _port_id)
{
    port_id = _port_id + ": ";

    fdcl::serial_port::init();
}


fdcl::serial_port::serial_port(sp_mode _mode)
{
    mode = _mode;

    fdcl::serial_port::init();
}


fdcl::serial_port::serial_port(std::string _port_id, sp_mode _mode)
{
    mode = _mode;
    port_id = _port_id + ": ";

    fdcl::serial_port::init();
}



fdcl::serial_port::~serial_port(void)
{
    if (is_open)
    {

        fdcl::serial_port::close();
    }
}

void fdcl::serial_port::close(void)
{
    int result = sp_close(port);
    if (result != SP_OK)
    {
        std::cerr << port_id << "cannot close " << serial_port_name 
                  << " properly!"
                  << std::endl;
    }
    else
    {
        std::cout << port_id << "serial port at " << serial_port_name 
                  << " closed."
                  << std::endl;
    }

    // clean exit the serial ports
    sp_free_port(port);

    is_open = false;
}


void fdcl::serial_port::init(void)
{
    port_name = "/dev/ttyUSB0";
    baud_rate = 9600;
}


void fdcl::serial_port::open(std::string _port_name)
{
    port_name = _port_name;
    
    fdcl::serial_port::open();
}


void fdcl::serial_port::open(std::string _port_name, int _baud_rate)
{
    port_name = _port_name;
    baud_rate = _baud_rate;

    fdcl::serial_port::open();
}


void fdcl::serial_port::open(std::string _port_name, int _baud_rate, \
    int _bit_size, sp_parity _parity, int _stop_bits
)
{
    port_name = _port_name;
    baud_rate = _baud_rate;
    bit_size = _bit_size;
    parity = _parity;
    stop_bits = _stop_bits;

    fdcl::serial_port::open();
}


void fdcl::serial_port::open(void)
{
    int result = 0;
    
    if (port_id == "")
    {
        port_id = port_name + ": ";
    }

    // parse the args
    serial_port_name = port_name.c_str();

    std::cout << port_id << "attempting to open " << serial_port_name
              << " with baud rate " << baud_rate
              << std::endl;

    // check for serial port name
    if (!serial_port_name)
    {
        std::cerr << port_id << "check the serial port path!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // check if device can be detected
    result = sp_get_port_by_name(serial_port_name, &port);
    if (result != SP_OK)
    {
        std::cerr << port_id << "cannot find the provided serial port!" 
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    // open device
    std::string mode_string;
    if (mode == SP_MODE_READ)
    {
        mode_string = "reading";
    }
    else if(mode == SP_MODE_WRITE)
    {
        mode_string = "writing";
    }
    else if(mode == SP_MODE_READ_WRITE)
    {
        mode_string = "reading/writing";
    }
    else
    {
        std::cerr << port_id << "invalid mode" << std::endl;
    }

    result = sp_open(port, mode);
    if (result != SP_OK)
    {
        std::cerr << port_id << "cannot open " << serial_port_name
                  << " for " << mode_string << " !"
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << port_id << "port is open for " << mode_string  << ".." 
              << std::endl;

    fdcl::serial_port::setup_port();
}


void fdcl::serial_port::setup_port(void)
{
    /* set the serial port options*/
    std::cout << port_id << "attempting to configure the serial port... "
              << std::endl;

    int result;

    // set baud rate
    result = sp_set_baudrate(port, baud_rate);
    if (result != SP_OK)
    {
        std::cerr << port_id << "cannot set port baud rate!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // set flow control
    result = sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE);
    if (result != SP_OK)
    {
        std::cerr << port_id << "cannot set flow control !" << std::endl;
                                           exit(EXIT_FAILURE);
    }

    // set bit size
    result = sp_set_bits(port, bit_size);
    if (result != SP_OK)
    {
        std::cerr << port_id << "cannot set data bits !" << std::endl;
        exit(EXIT_FAILURE);
    }

    // set parity
    result = sp_set_parity(port, parity);
    if (result != SP_OK)
    {
        std::cerr << port_id << "cannot set parity!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // set stop bits
    result = sp_set_stopbits(port, stop_bits);
    if (result != SP_OK)
    {
        std::cerr << port_id << "cannot set stop bits!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << port_id << "configuring serial port completed !" << std::endl;

    is_open  = true;
}


char fdcl::serial_port::read(char *byte_buff, int buff_len)
{
    int byte_num, bytes_waiting;

    bytes_waiting = sp_input_waiting(port);
    if (bytes_waiting >= buff_len)
    {
        int pos = 0;
        char byte_in[1];
        while (pos < bytes_waiting)
        {
            byte_num = sp_blocking_read_next(port, byte_in, 1, 0);
            byte_buff[pos] = byte_in[0];
            pos++;
        }

    }

    return *byte_in;
}


int fdcl::serial_port::read_line(char *byte_buff, int buff_len)
{
    int pos = 0;
    int byte_num, bytes_waiting;

    bytes_waiting = sp_input_waiting(port);
    if (bytes_waiting >= buff_len)
    {
        char byte_in[1];
        while (pos < bytes_waiting)
        {
            byte_num = sp_blocking_read_next(port, byte_in, 1, 0);
            byte_buff[pos] = byte_in[0];

            if (byte_in[0] == '\n') break;

            pos++;

            if (pos > buff_len - 1)
            {
                pos = 0;
                break;
            }
        }
    }

    return bytes_waiting;
}


int fdcl::serial_port::clear_buffer_until_newline(void)
{
    int pos = 0;
    int byte_num, bytes_waiting;

    char byte_in[1];
    while (true)
    {
        bytes_waiting = sp_input_waiting(port);
        if (bytes_waiting > 0)
        {
            byte_num = sp_blocking_read_next(port, byte_in, 1, 0);
            if (byte_in[0] == '\n') break;
        }
    }

    return byte_num;
}
