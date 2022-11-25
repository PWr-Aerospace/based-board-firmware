###############################################################################
# CMSIS
###############################################################################
set(CMSIS_DIR ${CMAKE_CURRENT_LIST_DIR}/CMSIS/)

set(CMSIS_INC 
  ${CMSIS_DIR}Device/ST/STM32F4xx/Include/
  ${CMSIS_DIR}Include/
)

add_library(CMSIS STATIC
  ${CMSIS_DIR}Device/ST/STM32F4xx/Source/gcc/system_stm32f4xx.c)

target_include_directories(CMSIS PUBLIC
  ${CMSIS_INC}
)

###############################################################################
# HAL
###############################################################################

set(HAL_DIR ${CMAKE_CURRENT_LIST_DIR}/STM32F4xx_HAL_Driver/)
set(HAL_INC ${HAL_DIR}Inc/)

set(HAL_SRC
  ${HAL_DIR}Src/stm32f4xx_hal.c
  ${HAL_DIR}Src/stm32f4xx_hal_cortex.c
  ${HAL_DIR}Src/stm32f4xx_hal_rcc_ex.c
  ${HAL_DIR}Src/stm32f4xx_hal_rcc.c
  ${HAL_DIR}Src/stm32f4xx_hal_gpio.c
  ${HAL_DIR}Src/stm32f4xx_hal_pwr.c
  ${HAL_DIR}Src/stm32f4xx_hal_pwr_ex.c
  ${HAL_DIR}Src/stm32f4xx_hal_sd.c
  ${HAL_DIR}Src/stm32f4xx_hal_spi.c
  ${HAL_DIR}Src/stm32f4xx_hal_uart.c
  ${HAL_DIR}Src/stm32f4xx_ll_sdmmc
)

#file(GLOB_RECURSE HAL_SRC ${HAL_DIR}/Src/*.*)

message("HAL FILES: " ${HAL_SRC})

add_library(HAL STATIC ${HAL_SRC})

target_include_directories(HAL PUBLIC
  ${CMSIS_INC}
  ${HAL_INC}
)

###############################################################################
# FatFs
###############################################################################
set(FATFS_DIR ${CMAKE_CURRENT_LIST_DIR}/FATFS)
set(FATFS_INC ${FATFS_DIR}/Inc/)

file(GLOB_RECURSE FATFS_SRC ${FATFS_DIR}/Src/*.*)

#message("FATFS FILES: " ${FATFS_SRC})

add_library(FATFS STATIC
  ${FATFS_SRC}
)

target_include_directories(FATFS PUBLIC
  ${HAL_INC}
  ${CMSIS_INC}
  ${FATFS_INC}
)

###############################################################################
# STARTUP
###############################################################################

add_library(STARTUP STATIC
  ${CMSIS_DIR}Device/ST/STM32F4xx/Source/gcc/startup_stm32f412retx.s)
