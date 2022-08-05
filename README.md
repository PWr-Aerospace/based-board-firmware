# About

Firmware for Absulute Chad project by PWr Aerospace
Currently, configired for STM32F401CCU6 STM32 BlackPill.

# Building step-by-step

Supported OS: Linux based, macOS

Partially supported (not tested xD): Windows

## Prerequisites
Firstly, clone this repo:

    git clone https://github.com/Aerospace-ASP/Firmware.git

Change directory:

    cd Firmware

To build the image for the target ARM architecture a cross-compilation toolchain is needed. To set this up, run toolchain/setup_arm_gcc.sh. This needs to be done only once after this project is cloned.

    ./toolchain/setup_arm_gcc.sh

## Building using GCC

You need to use the provided toolchain file and define the build type (Debug or Release) when configuring the build with cmake:

    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi-gcc-toolchain.cmake ..
    make -j`nrpoc`

**IMPORTANT** Change branch!

    git checkout -b branchName
    
## IDE using

Install CLion

Run CLion and load project (not working, alignment needed!)

1. CMake -> CMake Settings
* Set CMake Options -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-gcc-toolchain.cmake
* Set build directory to build
2. Click two times on prj/openocd/clion_debug_cfg.run/openocd debug & run.run.xml and load it (right-hand side)
3. Click the bug and enjoy!

When you finished - commit changes on own branch only! NOT on master! If you want to merge - make pull request

## Future toolchain improvements

https://github.com/ucgosupl/stm32f4_template
