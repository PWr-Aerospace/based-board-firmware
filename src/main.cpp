#include "bsp.h"
#include "fatfs.h"

FATFS fs;  // file system
FIL fil; // File
FILINFO fno;
FRESULT fresult;  // result
UINT br, bw;  // File read/write count*/

char path[20] = "/";
char name[20] = "test.txt";
char toWrite[100] = "Hello world from BaseBoard v1.0!!!";
UINT bytesWritten = 0;

int main()
{
    bsp_init_cpu();

    fresult = f_mount(&fs, path, 1);
    fresult = f_open(&fil, name, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
    f_write(&fil, toWrite, strlen(toWrite), &bytesWritten);
    fresult = f_close(&fil);
    fresult = f_mount(NULL, path, 1);

    while(true)
    {
        HAL_GPIO_TogglePin(PIN_LED_GPIO_Port, PIN_LED_Pin);
        HAL_Delay(1000);
    }
}
