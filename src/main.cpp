#include "bsp.h"
#include "fatfs.h"
#include "file_handling.h"

int main()
{
    bsp_init_cpu();

    Mount_SD("/");
    Format_SD();
    Create_File("FILE1.TXT");
    Create_File("FILE2.TXT");
    Unmount_SD("/");

    while(true)
    {
        HAL_GPIO_TogglePin(PIN_LED_GPIO_Port, PIN_LED_Pin);
        HAL_Delay(1000);
    }
}
