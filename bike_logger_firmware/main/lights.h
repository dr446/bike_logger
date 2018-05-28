#ifndef LIGHTS_H
#define LIGHTS_H

#include "Arduino.h"

extern int led;
extern int brightness;

void lights_initialise();
float light_sense_and_check();

#endif
