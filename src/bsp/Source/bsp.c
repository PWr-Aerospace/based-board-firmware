#include "bsp.h"

// #define LD2_Pin GPIO_PIN_5
// #define LD2_GPIO_Port GPIOA

static inline void error_handler() {
    while(1)
        ;
}

static void initLed() //todo: remove
{
    // GPIO_InitTypeDef GPIO_InitStruct = {0};

    // /* GPIO Ports Clock Enable */
    // __HAL_RCC_GPIOA_CLK_ENABLE();

    // /*Configure GPIO pin Output Level */
    // HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

    // /*Configure GPIO pin : LD2_Pin */
    // GPIO_InitStruct.Pin = LD2_Pin;
    // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    // HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
}

static void setup_cpu_clock() 
{
    // RCC_OscInitTypeDef RCC_OscInitStruct;
    // RCC_ClkInitTypeDef RCC_ClkInitStruct;

    // memset(&RCC_OscInitStruct, 0, sizeof(RCC_OscInitStruct));
    // memset(&RCC_ClkInitStruct, 0, sizeof(RCC_ClkInitStruct));

    // __HAL_RCC_GPIOC_CLK_ENABLE();
    // __HAL_RCC_GPIOA_CLK_ENABLE();

    // /** Configure LSE Drive Capability
    // */
    // HAL_PWR_EnableBkUpAccess();
    // __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
    // /** Initializes the RCC Oscillators according to the specified parameters
    // * in the RCC_OscInitTypeDef structure.
    // */
    // RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSI;
    // RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    // RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    // RCC_OscInitStruct.MSICalibrationValue = 0;
    // RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    // RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    // RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    // RCC_OscInitStruct.PLL.PLLM = 1;
    // RCC_OscInitStruct.PLL.PLLN = 40;
    // RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
    // RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    // RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    // if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    //     error_handler();
    // }
    // /** Initializes the CPU, AHB and APB buses clocks
    // */
    // RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    // RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    // RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    // RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    // RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    // if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
    //     error_handler();
    // }
    // /** Configure the main internal regulator output voltage
    // */
    // if(HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
    //     error_handler();
    // }
    // /** Enable MSI Auto calibration
    // */
    // HAL_RCCEx_EnableMSIPLLMode();

    // BSP_ASSERT(SystemCoreClock == OBC_CLOCK);
}

void bsp_init_cpu() {
    HAL_Init();
    setup_cpu_clock();
    initLed();
}

void bsp_panic() {
    while(1)
        ;
}
