#pragma once

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_pwr_ex.h"
#include "stm32f4xx_hal_rcc.h"

#ifdef __cplusplus
extern "C"
{
#endif

    // #define OBC_CLOCK 80000000U

#define PIN_LED_Pin GPIO_PIN_13
#define PIN_LED_GPIO_Port GPIOC
#define DBG1_Pin GPIO_PIN_13
#define DBG1_GPIO_Port GPIOC
#define Vsys_Pin GPIO_PIN_0
#define Vsys_GPIO_Port GPIOC
#define CS1_Pin GPIO_PIN_0
#define CS1_GPIO_Port GPIOA
#define CS2_Pin GPIO_PIN_1
#define CS2_GPIO_Port GPIOA
#define CS3_Pin GPIO_PIN_4
#define CS3_GPIO_Port GPIOA
#define CAM_PWR_Pin GPIO_PIN_4
#define CAM_PWR_GPIO_Port GPIOC
#define CAM_SIG_Pin GPIO_PIN_5
#define CAM_SIG_GPIO_Port GPIOC
#define S3_Pin GPIO_PIN_0
#define S3_GPIO_Port GPIOB
#define BR_DIR_Pin GPIO_PIN_1
#define BR_DIR_GPIO_Port GPIOB
#define DBG2_Pin GPIO_PIN_10
#define DBG2_GPIO_Port GPIOB
#define KEY_Pin GPIO_PIN_12
#define KEY_GPIO_Port GPIOB
#define SD_DET_Pin GPIO_PIN_8
#define SD_DET_GPIO_Port GPIOA
#define BW1_Pin GPIO_PIN_15
#define BW1_GPIO_Port GPIOA
#define BW2_Pin GPIO_PIN_3
#define BW2_GPIO_Port GPIOB
#define S1_Pin GPIO_PIN_4
#define S1_GPIO_Port GPIOB
#define S2_Pin GPIO_PIN_5
#define S2_GPIO_Port GPIOB
#define BR_A_Pin GPIO_PIN_8
#define BR_A_GPIO_Port GPIOB
#define BR_B_Pin GPIO_PIN_9
#define BR_B_GPIO_Port GPIOB

    void bsp_init_cpu();

    void bsp_panic();

    // #define BSP_ASSERT(cond) do { if(!(cond)) bsp_panic(); } while(0)

#ifdef __cplusplus
}
#endif
