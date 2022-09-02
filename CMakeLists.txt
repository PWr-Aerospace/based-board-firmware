set(CMAKE_SYSTEM_NAME Generic)
project(OBC C CXX ASM)
cmake_minimum_required(VERSION 3.10)

option(GENERATE_VERSION_HEADER "Generate version header"  ON)

# project settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ELF_FILE ${PROJECT_NAME}.elf)
set(HEX_FILE ${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_NAME}.bin)
set(HEX_FILEPATH ${CMAKE_BINARY_DIR}/${HEX_FILE})
set(BIN_FILEPATH ${CMAKE_BINARY_DIR}/${BIN_FILE})
set(ELF_FILEPATH ${CMAKE_BINARY_DIR}/${ELF_FILE})

message("-- Building OBC")

# add project source files
file(GLOB_RECURSE OBC_SRC src/*.*)

set(HAL
        3rdparty/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
        3rdparty/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
        3rdparty/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
        3rdparty/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
        3rdparty/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
        3rdparty/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
        3rdparty/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
        3rdparty/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
        3rdparty/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
        3rdparty/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sd.c)

SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/prj/linker/STM32F412RETX_FLASH.ld)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${LINKER_SCRIPT}")

add_library(CMSIS
        3rdparty/CMSIS/Device/ST/STM32F4xx/Source/gcc/system_stm32f4xx.c)

target_include_directories(CMSIS PUBLIC
        3rdparty/CMSIS/Include
        3rdparty/CMSIS/Device/ST/STM32F4xx/Include)

add_library(STARTUP
        3rdparty/CMSIS/Device/ST/STM32F4xx/Source/gcc/startup_stm32f412retx.s)

add_library(SD
	3rdparty/PROXY/SD/Src/diskio.c
	3rdparty/PROXY/SD/Src/fatfs.c
	3rdparty/PROXY/SD/Src/fatfs_platform.c
	3rdparty/PROXY/SD/Src/ff.c
	3rdparty/PROXY/SD/Src/ff_gen_drv.c
	3rdparty/PROXY/SD/Src/sd_diskio.c
	3rdparty/PROXY/SD/Src/bsp_driver_sd.c
	3rdparty/PROXY/SD/Src/file_handling.c
	3rdparty/PROXY/SD/Src/syscall.c)

target_include_directories(SD PUBLIC
		3rdparty/STM32F4xx_HAL_Driver/Inc
        3rdparty/CMSIS/Include
        3rdparty/CMSIS/Device/ST/STM32F4xx/Include
		src/bsp/configs
		src/bsp
		3rdparty/PROXY/SD/Inc)

add_executable(${ELF_FILE} ${OBC_SRC} ${HAL} ${LINKER_SCRIPT})

target_include_directories(${ELF_FILE} PUBLIC
        3rdparty/STM32F4xx_HAL_Driver/Inc
        3rdparty/PROXY/SD/Inc
        src/bsp
        src/bsp/configs
        3rdparty/CMSIS/Include
        3rdparty/CMSIS/Device/ST/STM32F4xx/Include
        )

target_link_libraries(${ELF_FILE} STARTUP CMSIS SD )
target_compile_options(${ELF_FILE} PRIVATE "-Wall" "-Wextra")

add_custom_target(build
        DEPENDS
        ${ELF_FILE})

add_custom_command(TARGET ${ELF_FILE} POST_BUILD
        COMMENT "Target size: ${ELF_FILE}"
        COMMAND ${CMAKE_OBJECT_SIZE} ${PROJECT_NAME}.elf)

add_custom_command(TARGET ${ELF_FILE} POST_BUILD
        COMMENT "Building: ${HEX_FILE}"
        COMMAND ${CMAKE_OBJECT_COPY} -Oihex $<TARGET_FILE:${ELF_FILE}> ${HEX_FILEPATH})

add_custom_command(TARGET ${ELF_FILE} POST_BUILD
        COMMENT "Building: ${BIN_FILE}"
        COMMAND ${CMAKE_OBJECT_COPY} -Obinary $<TARGET_FILE:${ELF_FILE}> ${BIN_FILEPATH})
