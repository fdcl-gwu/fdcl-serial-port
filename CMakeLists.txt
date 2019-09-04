
cmake_minimum_required (VERSION 3.1)
project(FDCL-Serial-Port)

set (CMAKE_CXX_STANDARD 11)

find_package (PkgConfig REQUIRED)

link_directories("/usr/local/lib/")
include_directories("/usr/local/include/")
include_directories(${PROJECT_SOURCE_DIR}/include)

pkg_check_modules(LIBSERIALPORT libserialport)
link_directories(${LIBSERIALPORT_LIBRARY_DIRS})
include_directories(${LIBSERIALPORT_INCLUDE_DIRS})


# FDCL serial port library
set(serial_port_src
    src/fdcl_serial_port.cpp
)
add_library(fdcl_serial_port STATIC ${serial_port_src})
target_link_libraries(fdcl_serial_port
    PUBLIC serialport
)

# Test library
set(test_serial_port_src
    src/main.cpp
)
add_executable(test_serial_port ${test_serial_port_src})