#ifndef SEV_SEG_INITIALISE_H
#define SEV_SEG_INITIALISE_H

#include <Wire.h>
#include "Arduino.h"
#include "Adafruit_MCP23008.h"


void sev_seg_initialise();

void sev_seg_set(int speed, int calories);

uint8_t segment_code(int number);

uint8_t add_dp(uint8_t seg_code);

uint8_t digit_code(uint8_t digit_disp);

#endif
