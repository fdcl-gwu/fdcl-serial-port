# FDCL-Serial-Port
This is a C++ wrapper for the `libserialport` library.

## Dependencies
`libserialport` is the only dependency for this library.
You can install with the following instructions.

For MacOS, you need to have [Homebrew](https://brew.sh/) installed in your system.

```sh
git submodule update --init
cd libraries/libserialport

# Linux
sudo apt-get -y install autoconf libtool automake 

# Mac (make sure Homebrew is installed)
brew install autoconf libtool automake

./autogen.sh
./configure
make
sudo make install
```

## Using the Library

### Testing the Code
1. Upload the `test_code.ino` in `arduino` directory to any Arduino board.
2. Update the `port_name` in `src/main/cpp` with the serial port name of the Arduino board.
3. Make sure you have installed all the dependencies as described above.
3. Compile the program:
    ```sh
    cd fdcl-serial-port
    mkdir build && cd build 
    cmake ../
    make
    ./test_serial_port
    ```

### As a CMake Library
1. Copy everything in this repository (or add as a submodule) to a subdirectory in your main project. Assume `<your project>/libraries/fdcl-serial-port`.
2. In the `CMakeLists.txt`, make the following changes:
    1. add header files: `include_directories(${PROJECT_SOURCE_DIR}/libraries/fdcl-serial-port/include)`
    2. add as a library: `add_subdirectory(${PROJECT_SOURCE_DIR}/libraries/fdcl-serial-port fdcl_serial_port)`
    3. link to the main executable/library: `target_link_libraries(<your project> PUBLIC fdcl_serial_port)`