#include "bsp.h"
#include "sd.h"

int main()
{
    bsp_init_cpu();

    SD_INIT();
    SD_MOUNT();
    SD_CREATE_FILE("file1.txt");
    SD_APPEND_TO_FILE(const_cast<char *>("Hello world"));
    SD_UNMOUNT();

    while(true)
    {
        HAL_GPIO_TogglePin(PIN_LED_GPIO_Port, PIN_LED_Pin);
        HAL_Delay(250);
    }
}
