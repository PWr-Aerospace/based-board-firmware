#ifndef _SD_PROXY_H_
#define _SD_PROXY_H_

#include "fatfs.h"
#include "ff.h"

FRESULT SD_Mount();
FRESULT SD_Create_file(const char *name);
FRESULT SD_Puts(const char *data);
FRESULT SD_Close_file();
FRESULT SD_Unmount();
FRESULT SD_Open_file(const char *name);

char *SD_Getline(char *buffer, int buffer_size);

#endif
