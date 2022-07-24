#pragma once

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_pwr_ex.h"
#include "stm32f4xx_hal_rcc.h"

#ifdef __cplusplus
extern "C" {
#endif

// #define OBC_CLOCK 80000000U

void bsp_init_cpu();

void bsp_panic();

// #define BSP_ASSERT(cond) do { if(!(cond)) bsp_panic(); } while(0)

#ifdef __cplusplus
}
#endif