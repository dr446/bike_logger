#ifndef SD_CONTROL_H
#define SD_CONTROL_H

#include <SPI.h>
#include <SD.h>
#include "Arduino.h"


const int chipSelect = 6;

void sd_initialise();

void sd_log_data(int time, float speed);

#endif
