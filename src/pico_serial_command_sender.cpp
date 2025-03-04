#include "pico_serial_command_sender.h"
#include <sstream>
#include <algorithm>

PicoSerialCommandSender::PicoSerialCommandSender(PicoSerialController& serialController)
    : serialController(serialController) {}

std::string PicoSerialCommandSender::capitalizeBooleansInJson(const std::string& jsonStr) {
    std::string result = jsonStr;
    // Replace lowercase true/false with capitalized True/False
    size_t pos = 0;
    while ((pos = result.find("true", pos)) != std::string::npos) {
        result.replace(pos, 4, "True");
        pos += 4;
    }
    pos = 0;
    while ((pos = result.find("false", pos)) != std::string::npos) {
        result.replace(pos, 5, "False");
        pos += 5;
    }
    return result;
}

std::vector<std::string> PicoSerialCommandSender::formatArgs(const std::vector<std::string>& args) {
    std::vector<std::string> formattedArgs;
    for (const auto& arg : args) {
        // If the argument looks like a JSON string, skip the extra quotes.
        if ((arg.front() == '{' && arg.back() == '}') || (arg.front() == '[' && arg.back() == ']')) {
            formattedArgs.push_back(arg);
        } else {
            formattedArgs.push_back("\"" + arg + "\"");
        }
    }
    return formattedArgs;
}

std::string PicoSerialCommandSender::sendCommand(const std::string& commandName, const std::vector<std::string>& args) {
    std::stringstream commandString;
    commandString << "run_command(\"" << commandName << "\"";

    if (!args.empty()) {
        commandString << ",";
        auto formattedArgs = formatArgs(args);
        for (size_t i = 0; i < formattedArgs.size(); ++i) {
            commandString << formattedArgs[i];
            if (i < formattedArgs.size() - 1) {
                commandString << ", ";
            }
        }
    }

    commandString << ")";
    std::string finalCommand = commandString.str();
    return serialController.sendCommand(finalCommand);
}

// Argument-less version of sendCommand
std::string PicoSerialCommandSender::sendCommand(const std::string& commandName) {
    std::stringstream commandString;
    commandString << "run_command(\"" << commandName << "\")";  // No args provided

    std::string finalCommand = commandString.str();
    return serialController.sendCommand(finalCommand);
}
