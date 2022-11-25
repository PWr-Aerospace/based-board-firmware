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
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/prj/linker/STM32F412RETX_FLASH.ld)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${LINKER_SCRIPT}")

message("-- Building OBC")

# add project source files
file(GLOB_RECURSE OBC_SRC src/*.*)

# add thirdparty libraries
add_subdirectory(3rdparty)

add_executable(${ELF_FILE} ${OBC_SRC} ${LINKER_SCRIPT})

target_include_directories(${ELF_FILE} PUBLIC
  ${HAL_INC}
  ${CMSIS_INC}
  ${FATFS_INC}
  src/bsp
  src/bsp/configs
  src/proxy/sd
)

target_link_libraries(${ELF_FILE} STARTUP FATFS HAL CMSIS)
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
