# How to use CLion?

- **ACHTUNG** - Make sure you have done all of initial steps from README!
- **ACHTUNG2** - Make sure you are on proper branch!


## Step by step

1. CMake -> CMake Settings

- Set CMake Options
`-DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi-gcc-toolchain.cmake`

- Set build directory to `build`

2. Click two times on `prj/openocd/clion_debug_cfg.run/openocd debug & run.run.xml`
   and load it (right-hand side)
   
3. Click the bug and enjoy!


# Known issues

### Error: Can't find interface/stlink.cfg in procedure 'script'
- Solution: `in prj/openocd/stm32l4discovery.cfg:7` replace 
`source [find interface/stlink.cfg]`
on
`source [find interface/stlink-v2-1.cfg]`
  
-- PLACEHOLDER TEXT



