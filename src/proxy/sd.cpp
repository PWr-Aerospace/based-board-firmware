#include "sd.h"

FATFS fs;
FATFS *pfs;
FIL fil;
FRESULT fres;
DWORD fre_clust;
uint32_t total, free_space;

void SD_INIT()
{
	MX_FATFS_Init();
}

FRESULT SD_MOUNT()
{
	return f_mount(&fs, "/", 0);
}

FRESULT SD_CREATE_FILE(const char* filename)
{
    return f_open(&fil, filename, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
}

void SD_APPEND_TO_FILE(char* content)
{
    f_puts(content, &fil);
}

FRESULT SD_UNMOUNT()
{
	f_close(&fil);
	f_mount(NULL, "", 1);
}
