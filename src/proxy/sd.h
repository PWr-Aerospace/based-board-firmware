#ifndef _SD_PROXY_
#define _SD_PROXY_

#include "fatfs.h"
#include "fatfs_sd.h"

void SD_INIT();
FRESULT SD_MOUNT();
FRESULT SD_CREATE_FILE(const char*);
void SD_APPEND_TO_FILE(char* content);
FRESULT SD_UNMOUNT();

#endif
