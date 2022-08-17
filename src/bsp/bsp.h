#pragma once

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_pwr_ex.h"
#include "stm32f4xx_hal_rcc.h"

#ifdef __cplusplus
extern "C" {
#endif

// #define OBC_CLOCK 80000000U

#define PIN_LED_Pin GPIO_PIN_13
#define PIN_LED_GPIO_Port GPIOC

#define SD_CS_Pin GPIO_PIN_14
#define SD_CS_GPIO_Port GPIOB

void bsp_init_cpu();

void bsp_panic();

// #define BSP_ASSERT(cond) do { if(!(cond)) bsp_panic(); } while(0)

#ifdef __cplusplus
}
#endif