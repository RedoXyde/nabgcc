# NabGCC

This a port of the Nabaztag's firmware sources for ARM GCC (and OSS tools).

# Improvements

- Cleanup
  - Fixed all types to use fixed size types from stdint.h
  - Removed lot of useless/debug/dead code
- **WPA2 support** (very experimental)

## Howto
### Requirements

    sudo apt install g++ gcc-arm-none-eabi gdb-arm-none-eabi php-cli g++-multilib 

### Get the sources

    git clone https://github.com/RedoXyde/nabgcc.git
    cd nabgcc
    git checkout wpa2
    git submodule update --init

### Compile

    cd nabgcc/
    make mtl_boot
    make -j2

### Flash
#### Using OpenOCD and GDB

    # Shell 1
    cd nabgcc/openocd/
    ./openocd -f ./nabaztagv2.cfg
    
    # Shell 2
    cd nabgcc/
    make program

#### Using the configuration page

    cd nabgcc/bin
    ../utils/mkfirmware.php
    
    # Then, put your Nabaztag in config mode (Blue leds) and upload the firmware0.0.0.13.sim file
    
