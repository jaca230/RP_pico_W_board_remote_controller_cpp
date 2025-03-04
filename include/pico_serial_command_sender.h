#ifndef PICO_SERIAL_COMMAND_SENDER_H
#define PICO_SERIAL_COMMAND_SENDER_H

#include <string>
#include <vector>
#include "pico_serial_controller.h"

class PicoSerialCommandSender {
public:
    explicit PicoSerialCommandSender(PicoSerialController& serialController);
    std::string sendCommand(const std::string& commandName, const std::vector<std::string>& args);
    std::string sendCommand(const std::string& commandName);


private:
    PicoSerialController& serialController;
    std::string capitalizeBooleansInJson(const std::string& jsonStr);
    std::vector<std::string> formatArgs(const std::vector<std::string>& args);
};

#endif // PICO_SERIAL_COMMAND_SENDER_H
