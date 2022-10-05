#include "bsp.h"
#include "fatfs.h"
#include "sd_proxy.h"
#include <cstring>

extern UART_HandleTypeDef huart1;

int main()
{
    bsp_init_cpu();
    char buf[100] = {0};
    char greeting[] = "BasedBoard v1.0 init\n\r";
    HAL_UART_Transmit(&huart1, (const uint8_t *)greeting, strlen(greeting), 1000);

    SD_Mount();
    SD_Open_file("file.txt");
    SD_Getline(buf, 100);
    SD_Close_file();
    SD_Unmount();

    HAL_UART_Transmit(&huart1, (const uint8_t *)buf, strlen(buf), 1000);

    while(true)
    {
        HAL_GPIO_TogglePin(PIN_LED_GPIO_Port, PIN_LED_Pin);
        HAL_Delay(1000);
    }
}
