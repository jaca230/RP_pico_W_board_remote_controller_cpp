#include <iostream>
#include <thread>
#include <chrono>
#include "pico_serial_controller.h"
#include "pico_serial_command_sender.h"

int main() {
    // Initialize the serial controller with the appropriate port and settings
    PicoSerialController serialController("/dev/ttyACM0", LibSerial::BaudRate::BAUD_115200, 
                                          LibSerial::Parity::PARITY_EVEN, LibSerial::StopBits::STOP_BITS_1, 
                                          1000, true);  // Adjust port and baud rate as needed

    try {
        // Connect to the serial port
        serialController.connect();

        // Initialize the command sender
        PicoSerialCommandSender commandSender(serialController);

        std::vector<std::string> args;

        // List available commands
        std::cout << "Available commands:" << std::endl;
        std::string response = commandSender.sendCommand("list_commands");
        std::cout << response << '\n' << std::endl;

        // Get the entire configuration
        std::cout << "Current configuration:" << std::endl;
        response = commandSender.sendCommand("get_all_config");
        std::cout << response << '\n' << std::endl;

        // Create a GPIO hardware (like an LED)
        std::cout << "Creating GPIO hardware..." << std::endl;
        std::string settings = R"({"pin_number": "LED", "mode": "OUT", "value": 0, "start_on_init": True})";
        args = {"gpio", settings, "test_gpio"};
        std::cout << commandSender.sendCommand("create", args) << '\n' << std::endl;

        // Start the GPIO hardware
        std::cout << "Starting GPIO hardware..." << std::endl;
        args = {"test_gpio"};
        std::cout << commandSender.sendCommand("start", args) << '\n' << std::endl;

        // Set GPIO value to 1 (turn on LED)
        std::cout << "Setting GPIO value to 1 (turn on LED)..." << std::endl;
        settings = R"({"value": 1})";
        args = {"test_gpio", settings};
        std::cout << commandSender.sendCommand("apply_hardware_settings", args) << '\n' << std::endl;

        // Get the updated configuration
        std::cout << "Updated configuration (after turning LED on):" << std::endl;
        response = commandSender.sendCommand("get_all_config");
        std::cout << response << '\n' << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));  // Wait for 1 second

        // Set GPIO value back to 0 (turn off LED)
        std::cout << "Setting GPIO value to 0 (turn off LED)..." << std::endl;
        settings = R"({"value": 0})";
        args = {"test_gpio", settings};
        std::cout << commandSender.sendCommand("apply_hardware_settings", args) << '\n' << std::endl;

        // Get the updated configuration
        std::cout << "Updated configuration (after turning LED off):" << std::endl;
        response = commandSender.sendCommand("get_all_config");
        std::cout << response << '\n' << std::endl;

        // Save the current configuration
        std::cout << "Saving current configuration..." << std::endl;
        std::cout << commandSender.sendCommand("save_config") << '\n' << std::endl;

        // Delete the test GPIO hardware
        std::cout << "Deleting test GPIO hardware..." << std::endl;
        args = {"test_gpio"};
        std::cout << commandSender.sendCommand("delete", args) << '\n' << std::endl;

        // Get the entire configuration after deletion
        std::cout << "Updated configuration (after deleting test GPIO):" << std::endl;
        response = commandSender.sendCommand("get_all_config");
        std::cout << response << '\n' << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));  // Wait for 1 second

        // Load the saved configuration
        std::cout << "Loading saved configuration..." << std::endl;
        std::cout << commandSender.sendCommand("load_config") << '\n' << std::endl;

        // Get the entire configuration
        std::cout << "Updated configuration (after loading saved config):" << std::endl;
        response = commandSender.sendCommand("get_all_config");
        std::cout << response << '\n' << std::endl;

        // Optionally, apply the saved configuration again
        std::cout << "Applying saved configuration..." << std::endl;
        std::cout << commandSender.sendCommand("apply_config") << '\n' << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    // Close the serial connection
    serialController.close();

    return 0;
}
