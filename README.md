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