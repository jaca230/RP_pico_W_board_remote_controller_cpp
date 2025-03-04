#ifndef PICO_SERIAL_CONTROLLER_H
#define PICO_SERIAL_CONTROLLER_H

#include <string>
#include <libserial/SerialPort.h>

class PicoSerialController {
public:
    // Constructor with default values
    PicoSerialController(const std::string& port, 
                         LibSerial::BaudRate baudrate = LibSerial::BaudRate::BAUD_115200, 
                         LibSerial::Parity parity = LibSerial::Parity::PARITY_EVEN,
                         LibSerial::StopBits stopBits = LibSerial::StopBits::STOP_BITS_1,
                         size_t timeout_ms = 1000,  // Renamed timeout to timeout_ms for clarity
                         bool debug = false);

    // Connect to the serial port
    void connect();

    // Send a command and get the response
    std::string sendCommand(const std::string& command);

    // Close the connection
    void close();

private:
    std::string port;
    LibSerial::BaudRate baudrate;       // Baud rate
    LibSerial::Parity parity;           // Parity
    LibSerial::StopBits stopBits;       // Stop bits
    uint32_t timeout_ms;                // Timeout in milliseconds
    LibSerial::SerialPort serialConn;   // Serial port object
    bool debug;                         // Debug flag
};

#endif // PICO_SERIAL_CONTROLLER_H
