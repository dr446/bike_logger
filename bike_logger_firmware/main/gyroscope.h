#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "Arduino.h"
#include "hall_effect.h"
#include<Wire.h>

extern float user_mass;
extern float g;

void gyroscope_initialise();

//returns incline in degrees.
float getincline();

float estimate_calories(float incline, float speed);


#endif
