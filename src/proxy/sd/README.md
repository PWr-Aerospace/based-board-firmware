# SD card

## Custom layer usage

The purpose of this file is to provide a set of easy to use functions for file handling. The main advantage is that you don't have to go into details how the FatFs library work.

### Read a line from a file

```cpp
#include "sd_proxy.h"

char *buf[100] = {0};

SD_Mount();                 // Create a logical volume
SD_Open_file("file.txt");   // Open an exisiting file
SD_Getline(buf, 100);       // Get and store line from file in buf
SD_Close_file();            // Close file
SD_Unmount();               // Delete the logical volume

```

### Write a line to a file

```cpp
#include "sd_proxy.h"

char *buf[100] = {0};

SD_Mount();                 // Create a logical volume
SD_Create_file("file.txt"); // Open an exisiting file
SD_Write("Hello world");    // Get and store line from file in buf
SD_Close_file();            // Close file
SD_Unmount();               // Delete the logical volume

```

When you use those functions you don't have to worry about file sync and creating logical volumes or files.

## FatFs usage

In more advanced usage, the direct calls to fatfs library would be better. This way you can use more than one file, sync them whenever you want or even use printf().
### Read a line from a file
```cpp
#include "fatfs.h"

const int buffer_size = 100;
char buffer [buffer_size] = {0};

FATFS fs;           // file system
FIL fil;            // File
UINT br, bw;        // File read/write count*/

f_mount(&fs, "/", 1);
f_open(&fil, "file.txt", FA_OPEN_ALWAYS | FA_READ);
f_gets(buffer, buffer_size, &fil);
f_close(&fil);
f_mount(NULL, "/",, 1);
```
### Write a line to a file

```cpp
#include "fatfs.h"

char board_name [] = "Based Board v1.0";

FATFS fs;           // file system
FIL fil;            // File
UINT br, bw;        // File read/write count*/

f_mount(&fs, "/", 1);
f_open(&fil, "file.txt", FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
f_printf(&fil,"Hello world from %s\n", board_name);
f_close(&fil);
f_mount(NULL, "/",, 1);
```
NOTE: you can call `f_write()` many times, but the files are update only when you call `f_close()` or `f_sync()`. If you don't sync your files periodically and the board loses power, you lose all of the unsynced data! 

## Performance tests

| File size | Writes | Total size | Time    |
|------     |  ----  | ---        | ---     |
| 1kB       | 1024   | 1 MB       | 350 ms  |
| 128 B     | 8192   | 1 MB       | 2.5 s   |
| 1kB       | 102400 | 100 MB     | 22.30 s |
| 128 B     | 819200 | 100 MB     | 8.2 s   |

Tests were performed using custom proxy functions. Clearly, the more frequent the file is updated, the shorter time it takes to complete the save.
Small times weer measured using `HAL_GetTick()` function, the longer times using stopwatch.

## Other

The pin that should detect the SD card doesn't work properly, do not use it with Based Board v1.0.