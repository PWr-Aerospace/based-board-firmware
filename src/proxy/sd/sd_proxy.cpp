#include "sd_proxy.h"
#include "ff.h"
#include "stdarg.h"

int strlen(const char *input);

FATFS fs; // file system
FIL fil;  // File
FILINFO fno;
UINT br, bw; // File read/write count*/

char path[20] = "/";

FRESULT SD_Mount()
{
    return f_mount(&fs, path, 1);
}

FRESULT SD_Create_file(const char *name)
{
    return f_open(&fil, name, FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
}

FRESULT SD_Open_file(const char *name)
{
    return f_open(&fil, name, FA_OPEN_ALWAYS | FA_READ);
}

FRESULT SD_Puts(const char *data)
{
    FRESULT fres = f_write(&fil, data, strlen(data), &bw);
    f_sync(&fil);
    return fres;
}

FRESULT SD_Close_file()
{
    return f_close(&fil);
}

FRESULT SD_Unmount()
{
    return f_mount(NULL, path, 1);
}

char *SD_Getline(char *buffer, int buffer_size)
{
    f_gets(buffer, buffer_size, &fil);
    return buffer;
}

int strlen(const char *input)
{
    int length = 0;
    while(input[length] != 0)
    {
        length++;
    }
    return length;
}
