# About

Firmware for Absulute Chad project by PWr Aerospace
Currently, configired for STM32F401CCU6 STM32 BlackPill.

# Building step-by-step

Supported OS: Linux based, macOS

Partially supported (not tested xD): Windows

## Install dependencies

`Ubuntu`/`Debian`:

```bash
sudo apt-get update && sudo apt-get install -y gcc-arm-none-eabi cmake git stlink-tools lbzip2 wget curl clang-format clang-tidy openocd minicom
```

`macOS` (assuming [brew](https://brew.sh/) is already installed):

```bash
brew install --cask gcc-arm-embedded && brew install stlink cmake clang-format llvm minicom openocd && \
ln -s "$(brew --prefix llvm)/bin/clang-format" "/usr/local/bin/clang-format" && \
ln -s "$(brew --prefix llvm)/bin/clang-tidy" "/usr/local/bin/clang-tidy" && \
ln -s "$(brew --prefix llvm)/bin/clang-apply-replacements" "/usr/local/bin/clang-apply-replacements"
```

## Get the code

Firstly, clone this repo:

```bash
git clone https://github.com/Aerospace-ASP/Firmware.git
```

Change directory:

```bash
cd Firmware
```

To build the image for the target ARM architecture a cross-compilation toolchain is needed. To set this up, run toolchain/setup_arm_gcc.sh. This needs to be done only once after this project is cloned.

```bash
./toolchain/setup_arm_gcc.sh
```

## Building using GCC

You need to use the provided toolchain file and define the build type (Debug or Release) when configuring the build with cmake:

```bash
mkdir build && \
cd build && \
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi-gcc-toolchain.cmake .. && \
make -j`nrpoc`
```

**IMPORTANT** Change branch!

```bash
git checkout -b branch_name
```

## IDE using

Install CLion

Run CLion and load project

1. CMake -> CMake Settings

    * Set CMake Options `-DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-gcc-toolchain.cmake`
    * Set build directory to build

2. Click two times on `prj/openocd/clion_debug_cfg.run/openocd debug & run.run.xml` and load it (right-hand side)
3. Click the bug and enjoy!

When you finished - commit changes on own branch only! NOT on master! If you want to merge - make pull request

## Future toolchain improvements

<https://github.com/ucgosupl/stm32f4_template>

to installl
lbzip2 cmake
