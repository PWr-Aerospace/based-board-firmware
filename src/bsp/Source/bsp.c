#include "bsp.h"

// #define LD2_Pin GPIO_PIN_5
// #define LD2_GPIO_Port GPIOA

static inline void error_handler() {
    while(1)
    {
        HAL_GPIO_WritePin(PIN_LED_GPIO_Port, PIN_LED_Pin, GPIO_PIN_SET);
    }
}

static inline void Error_Handler() {
    while(1)
    {
        HAL_GPIO_WritePin(PIN_LED_GPIO_Port, PIN_LED_Pin, GPIO_PIN_SET);
    }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(PIN_LED_GPIO_Port, PIN_LED_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : PIN_LED_Pin */
    GPIO_InitStruct.Pin = PIN_LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PIN_LED_GPIO_Port, &GPIO_InitStruct);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
static void setup_cpu_clock() 
{
            RCC_OscInitTypeDef RCC_OscInitStruct = {0};
            RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

            /** Configure the main internal regulator output voltage
      */
            __HAL_RCC_PWR_CLK_ENABLE();
            __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

            /** Initializes the RCC Oscillators according to the specified parameters
      * in the RCC_OscInitTypeDef structure.
      */
            RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
            RCC_OscInitStruct.HSEState = RCC_HSE_ON;
            RCC_OscInitStruct.LSIState = RCC_LSI_ON;
            RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
            RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
            RCC_OscInitStruct.PLL.PLLM = 8;
            RCC_OscInitStruct.PLL.PLLN = 100;
            RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
            RCC_OscInitStruct.PLL.PLLQ = 4;
            RCC_OscInitStruct.PLL.PLLR = 2;
            if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
            {
                Error_Handler();
            }

            /** Initializes the CPU, AHB and APB buses clocks
      */
            RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                          |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
            RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
            RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
            RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
            RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

            if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
            {
                Error_Handler();
            }


            RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

            /** Initializes the peripherals clock
      */
            PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_PLLI2S|RCC_PERIPHCLK_CLK48
                                                       |RCC_PERIPHCLK_SDIO;
            PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
            PeriphClkInitStruct.PLLI2S.PLLI2SM = 8;
            PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
            PeriphClkInitStruct.PLLI2S.PLLI2SQ = 8;
            PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48CLKSOURCE_PLLI2SQ;
            PeriphClkInitStruct.SdioClockSelection = RCC_SDIOCLKSOURCE_CLK48;
            PeriphClkInitStruct.PLLI2SSelection = RCC_PLLI2SCLKSOURCE_PLLSRC;
            if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
            {
                Error_Handler();
            }

}

void bsp_init_cpu()
{
    HAL_Init();
    setup_cpu_clock();
    GPIO_Init();
}

void bsp_panic()
{
    while(1)
        ;
}
