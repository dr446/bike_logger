#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <TimeLib.h>
#include <Time.h>
#include "sev_seg_initialise.h"
#include "hall_effect.h"
#include "sd_control.h"

float current_speed;
float current_time;

void setup() {
Serial.print(current_time);
  Serial.begin(9600);
  
  sev_seg_initialise();

  sd_initialise();

  //set up interrupt service routine that is triggered by the hall effect sensor input falling edge
  pinMode(HALL_EFFECT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(HALL_EFFECT_PIN), update_current_time, FALLING);
  
}

void loop() {
  
  current_speed = calculate_speed();
  sd_log_data(current_time, current_speed);

  sev_seg_set(current_speed);
  
}
