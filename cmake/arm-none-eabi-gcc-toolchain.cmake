set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PATH "/opt/homebrew/")

execute_process (
    COMMAND bash -c "dirname $(which arm-none-eabi-gcc) | tr -d '\n'"
    OUTPUT_VARIABLE outVar
)

if(outVar STREQUAL "")
    set(TOOLCHAIN_PATH "${CMAKE_CURRENT_LIST_DIR}/../toolchain/gcc-arm-none-eabi")
else()
    message("Found toolchain at: ${outVar}")
    set(TOOLCHAIN_PATH "${outVar}")
endif()

SET(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-g++)
SET(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)
SET(CMAKE_OBJECT_COPY ${TOOLCHAIN_PATH}/arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PATH}/arm-none-eabi-objdump)
SET(CMAKE_OBJECT_SIZE ${TOOLCHAIN_PATH}/arm-none-eabi-size)

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

SET(COMMON_COMPILE_FLGS "-Wall -Wextra -Wpedantic -O0 -g -fno-common -fmessage-length=0 -gdwarf-2")
SET(COMMON_CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mthumb-interwork -ffunction-sections -fdata-sections -DSTM32F401xx -mfloat-abi=hard -mfpu=fpv4-sp-d16")
SET(LINKER_FLAGS "-Wl,--print-memory-usage,-Map=${PROJECT_NAME}.map,-gc-sections -lc -lm -specs=nano.specs -specs=nosys.specs -mfloat-abi=hard -mfpu=fpv4-sp-d16")
SET(LINKER_WRAPPER_FLAGS "-Wl,-wrap=malloc,-wrap=calloc,-wrap=free,-wrap=_malloc_r,-wrap=_calloc_r,-wrap=_free_r")

SET(CMAKE_C_FLAGS "${COMMON_COMPILE_FLGS} ${COMMON_CPU_FLAGS} -std=c17" CACHE STRING "" FORCE)
SET(CMAKE_CXX_FLAGS "${COMMON_COMPILE_FLGS} ${COMMON_CPU_FLAGS} -std=c++2a -fno-exceptions -fno-rtti -fno-unwind-tables -Wno-volatile" CACHE STRING "" FORCE)
SET(CMAKE_ASM_FLAGS "-x assembler-with-cpp"  CACHE INTERNAL "" FORCE)
SET(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS} ${LINKER_WRAPPER_FLAGS}" CACHE STRING "" FORCE)
