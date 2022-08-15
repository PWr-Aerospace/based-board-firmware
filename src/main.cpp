#include "bsp.h"
#include "fatfs.h"
#include "fatfs_sd.h"
#include "string.h"

SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart1;

FATFS fs;
FATFS *pfs;
FIL fil;
FRESULT fres;
DWORD fre_clust;
uint32_t total, free_space;
char buffer[100];

static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
void send_message(const char *message);

int main()
{
    bsp_init_cpu();

    MX_SPI1_Init();
    MX_USART1_UART_Init();
    MX_FATFS_Init();

    FRESULT fres = f_mount(&fs, "/", 0);
    if(fres != FR_OK)
    {
        send_message("mount failed");
    }

    /* Open file to write */
    fres = f_open(&fil, "first.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
    HAL_Delay(2000);
    if(fres != FR_OK)
        send_message("file opening failed!\n");

    /* Check free space */
    if(f_getfree("", &fre_clust, &pfs) != FR_OK)
        send_message("checking free space failed");

    total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
    free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);

    /* Free space is less than 1kb */
    if(free_space < 1)
        send_message("free space less than 1kb");

    /* Writing text */
    f_puts("STM32 SD Card I/O Example via SPI\n", &fil);
    f_puts("Save the world!!!", &fil);
    f_puts("New sketch compiled with ASP toolchain", &fil);

    /* Close file */
    if(f_close(&fil) != FR_OK)
        send_message("closing file failed");

    /* Unmount SDCARD */
    if(f_mount(NULL, "", 1) != FR_OK)
        send_message("Unmounting failed");

    while(true)
    {
        HAL_GPIO_TogglePin(PIN_LED_GPIO_Port, PIN_LED_Pin);
        HAL_Delay(250);
    }
}

void send_message(const char *message)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 1000);
    while(1)
    {
    }
}

void Error_Handler()
{
    while(1)
    {
    }
}

static void MX_SPI1_Init(void)
{

    /* USER CODE BEGIN SPI1_Init 0 */

    /* USER CODE END SPI1_Init 0 */

    /* USER CODE BEGIN SPI1_Init 1 */

    /* USER CODE END SPI1_Init 1 */
    /* SPI1 parameter configuration*/
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;
    if(HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN SPI1_Init 2 */

    /* USER CODE END SPI1_Init 2 */
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if(HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */
}
