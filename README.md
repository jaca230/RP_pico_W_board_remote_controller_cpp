# Pico Board Remote Controller (C++ Version)

The **Pico Board Remote Controller** is a C++ library for controlling the Raspberry Pi Pico W board via serial communication. It provides functionality for managing GPIO, PWM, and other hardware components through a structured and efficient interface. This controller enables sending commands to the board for configuring, controlling, and retrieving hardware settings, making it ideal for embedded and automation projects. This is the C++ version of the [python pico w board remote controller](https://github.com/jaca230/RP_pico_W_board_remote_controller).

## Features

- **Serial Communication**: Communicate with the Raspberry Pi Pico W via USB serial.
- **GPIO Control**: Create, start, and manage GPIO hardware like LEDs, buttons, and more.
- **PWM Management**: Control PWM pins for devices such as motors or servos.
- **Configuration Management**: Save, load, and apply configuration settings for easy setup and replication.
- **C++ Implementation**: Designed for integration with embedded systems.

## Installation

To build and run this project, you need the following dependencies installed:

### **System Requirements**  
- **C++17 or later**  
- **CMake 3.10+**  
- **Make (GNU Make or equivalent)**  
- **GCC / Clang / MSVC (any modern C++ compiler)**  

### **Required Libraries**  
These libraries must be installed before building the project:

| Library | Description | Installation Command (Debian/Ubuntu) |
|---------|------------|--------------------------------------|
| [LibSerial](https://libserial.readthedocs.io/en/latest/) | C++ library for serial communication | `sudo apt install libserial-dev` |

### Cloning the Repository

Clone the repository and initialize the submodule containing board-related files:

```bash
git clone --recurse-submodules https://github.com/jaca230/RP_pico_W_board_remote_controller_cpp.git
cd RP_pico_W_board_remote_controller_cpp
```

If you've already cloned the repository without submodules, you can initialize them later:

```bash
git submodule update --init --recursive
```

### Board Files  
Upload the board files to your Pico following the README in the `board_files` submodule:  
[Board Files GitHub Page](https://github.com/jaca230/RP_pico_W_board_interface)

## Building, Installing, and Running

This project includes convenient scripts for building, installing, and running the controller:

1. **Build the Project**  
   To build the project, run:

   ```bash
   ./scripts/build.sh
   ```

   Use `-o` or `--overwrite` to clean the previous build before rebuilding:

   ```bash
   ./scripts/build.sh --overwrite
   ```

2. **Install the Project**  
   To install the project system-wide (default install path: `/usr/local`):

   ```bash
   ./scripts/install.sh
   ```

   You can specify a different install prefix:

   ```bash
   ./scripts/install.sh --prefix /custom/install/path
   ```

   Use `-o` or `--overwrite` to clean and reinstall:

   ```bash
   ./scripts/install.sh --overwrite
   ```

3. **Run the Controller**  
   Once built, you can run the `main.cpp` example with. You must make sure the [board files](https://github.com/jaca230/RP_pico_W_board_interface) are uploaded to the RP Pico W. Edit the constructor at the top to point to the correct serial device:
   ```cpp
    PicoSerialController serialController("/dev/ttyACM0", LibSerial::BaudRate::BAUD_115200, 
                                        LibSerial::Parity::PARITY_EVEN, LibSerial::StopBits::STOP_BITS_1, 
                                        1000, true);  // Adjust port and baud rate as needed
   ```

   Then you can test flashing and LED on and off using the generated executable from main. 

   ```bash
   ./scripts/run.sh
   ```

   To run the executable with a debugger (`gdb`):

   ```bash
   ./scripts/run.sh --debug
   ```

## Configuration Management

The controller allows you to save, load, and apply configurations at any time to preserve your hardware setup between sessions. Commands like `save_config` and `load_config` enable persistent configurations.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Links

- [Raspberry Pi Pico Documentation](https://www.raspberrypi.org/documentation/pico/)
- [LibSerial Documentation](https://libserial.readthedocs.io/en/latest/)
- [CMake Documentation](https://cmake.org/documentation/)  