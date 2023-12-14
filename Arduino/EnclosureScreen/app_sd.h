#ifndef APP_SD_H
#define APP_SD_H

#include <SD.h>

void sd_setup();
int SD_init();
void listDir(fs::FS & fs, const char *dirname, uint8_t levels);

#endif