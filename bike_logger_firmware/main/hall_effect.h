#ifndef HALL_EFFECT_H
#define HALL_EFFECT_H

#include <TimeLib.h>
#include <Time.h>
#include "Arduino.h"

#define HALL_EFFECT_PIN   2

extern float current_time;
extern float pi;

float calculate_speed();

//ISR
void update_current_time();

#endif
