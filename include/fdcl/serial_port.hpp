#ifndef FDCL_SERIAL_PORT_HPP
#define FDCL_SERIAL_PORT_HPP

#include <libserialport.h>
#include <iostream>
#include <iostream>

namespace fdcl
{
class serial_port
{
public:
    serial_port(void);
    serial_port(std::string _port_id);
    serial_port(sp_mode _mode);
    serial_port(std::string _port_id, sp_mode _mode);
    ~serial_port(void);

    bool is_open = false; /** Flag to check is the serial port is open or not */

    std::string port_name;  /**< Name of the serial port */
    unsigned int baud_rate; /**< Baud rate of the serial port*/

    void open(std::string _port_name);
    void open(std::string _port_name, int _baud_rate);
    void open(std::string _port_name, int _baud_rate, sp_parity _parity);
    void open(std::string _port_name, int _baud_rate, int _bit_size, \
        sp_parity _parity, int _stop_bits
    );

    char read(char *byte_buff, int buff_len);
    int read_line(char *byte_buff, int buff_len);

    void close(void);

private:
    std::string port_id = ""; /** Unique name to identify the serial port */
    const char *serial_port_name = NULL; /**< Name of the serial port, must be 
                                           * set through the port_name.
                                           */

    struct sp_port *port; /**< Port structure for the serial port. Uses
                           * libserialport as the serial port.
                           */

    sp_mode mode = SP_MODE_READ;
    sp_parity parity = SP_PARITY_NONE;
    int bit_size = 8;
    int stop_bits = 1;

    // int buff_len;      /**< Buffer length for the data comming from the port */
    // char byte_buff[100]; /**< Buffer to save incoming bytes */
    char byte_in[1];   /**< Char to collect each incoming byte */
  
    /** \fn void setup(int baud)
    * Setups the serial port for the Lidar with the recommended
    * configurations. This is called through the void open() function.
    */
    void setup_port(void);

    void open(void);

    void init(void);

};  // end of class serial_port
}  // end of namespace fdcl

#endif