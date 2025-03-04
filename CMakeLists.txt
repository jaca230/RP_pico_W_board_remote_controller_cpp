cmake_minimum_required(VERSION 3.10)

# Project name and version
project(pico_remote_board_controller)

# Set the output directories for the build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Specify include directories
include_directories(include)

# Gather all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create a static library from all source files
add_library(pico_remote_board_controller STATIC ${SOURCES})

# Specify link libraries for the static library
target_link_libraries(pico_remote_board_controller serial)

# Create the executable
add_executable(main main.cpp)

# Link the executable with the static library
target_link_libraries(main PRIVATE pico_remote_board_controller)

# Specify where to install the header files and library
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/pico_remote_board_controller)

# Install the library into /usr/local/pico_remote_board_controller/lib
install(TARGETS pico_remote_board_controller DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

# Do not install the executable by default
# Uncomment the following line to install the executable if needed:
# install(TARGETS pico_remote_board_controller_main DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
