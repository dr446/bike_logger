#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <TimeLib.h>
#include <Time.h>
#include "sev_seg_initialise.h"
#include "hall_effect.h"
#include "sd_control.h"

int currenttime;

void setup() {

  sev_seg_initialise();

  sd_initialise();

  
}

void loop() {

  float current_speed = calculate_speed();
 
  sd_log_data(currenttime, current_speed);

  sev_seg_set(current_speed);
  
}
