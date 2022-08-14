#include "bsp.h"

int main()
{
    bsp_init_cpu();

    while(true)
    {
        HAL_GPIO_TogglePin(PIN_LED_GPIO_Port, PIN_LED_Pin);
        HAL_Delay(250);
    }
}
