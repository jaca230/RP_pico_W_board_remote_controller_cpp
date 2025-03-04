#include "pico_serial_controller.h"
#include <iostream>
#include <stdexcept>
#include <regex>
#include <libserial/SerialPort.h>
#include <libserial/SerialPortConstants.h> // Include the constants header

// Constructor with default values
PicoSerialController::PicoSerialController(const std::string& port, 
                                           LibSerial::BaudRate baudrate, 
                                           LibSerial::Parity parity, 
                                           LibSerial::StopBits stopBits, 
                                           size_t timeout_ms, 
                                           bool debug)
    : port(port), baudrate(baudrate), parity(parity), stopBits(stopBits), timeout_ms(timeout_ms), debug(debug) {}

void PicoSerialController::connect() {
    try {
        serialConn.Open(port);  // Open the serial port
        
        // Set baud rate using the passed enum
        serialConn.SetBaudRate(baudrate);  // Use the proper baud rate enum

        // Convert timeout from milliseconds to deciseconds
        short timeout_in_deciseconds = static_cast<short>(timeout_ms / 100); // 1 decisecond = 100 milliseconds
        serialConn.SetVTime(timeout_in_deciseconds);  // Set the timeout in deciseconds
        
        // Set parity using the passed parity enum
        serialConn.SetParity(parity);

        // Set the number of stop bits using the passed stop bits enum
        serialConn.SetStopBits(stopBits);

        std::cout << "Connected to " << port << std::endl;
    } catch (const LibSerial::OpenFailed& e) {
        std::cerr << "Error connecting to " << port << ": " << e.what() << std::endl;
    }
}

std::string PicoSerialController::sendCommand(const std::string& command) {
    if (!serialConn.IsOpen()) {
        std::cerr << "Not connected to the serial port." << std::endl;
        return "";
    }

    // In debug mode, print the command being sent
    if (debug) {
        std::cout << "Sending command: " << command << std::endl;
    }

    // Send the command with proper line termination
    serialConn.Write(command + "\r");

    // Read the response until the delimiter ">>>"
    std::string response;
    std::string line;
    
    // Loop to read lines until we find the ">>>"
    try {
        // Loop to read lines until we find the ">>>"
        do {
            serialConn.ReadLine(line, '\n', timeout_ms);  // Read a line with a timeout
            response += line;  // Append the line to the response string
        } while (response.find("<==]") == std::string::npos && response.size() < 1024);  // Stop once ">>>" is found or buffer size limit
    } catch (const std::runtime_error& e) {
        // Handle timeout or any other read error
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    // Check if we found the response
    if (response.find("<==]") != std::string::npos) {
        // Strip leading and trailing whitespace
        response = std::regex_replace(response, std::regex("^\\s+|\\s+$"), "");
        
        // Use regex to find "RESPONSE: [==>message<==]"
        std::smatch match;
        if (std::regex_search(response, match, std::regex("RESPONSE:\\s?\\[==>([\\s\\S]*?)<==\\]"))) {
            return match.str(1);  // Extract the message within the delimiters
        } else {
            // Append the raw response to the error message if debug is enabled
            if (debug) {
                return "No valid response found or invalid format. No match to regex. Raw response: " + response;
            }
            return "No valid response found or invalid format. No match to regex.";
        }
    } else {
        // Return raw response in debug mode if no valid response
        if (debug) {
            return "No valid response found or invalid format. No end marker found. Raw response: " + response;
        }
        return "No valid response found or invalid format. No end marker found.";
    }
}


void PicoSerialController::close() {
    if (serialConn.IsOpen()) {
        serialConn.Close();
        std::cout << "Connection to " << port << " closed." << std::endl;
    }
}
