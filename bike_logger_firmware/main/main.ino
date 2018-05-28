#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <TimeLib.h>
#include <Time.h>
#include "sev_seg_initialise.h"
#include "hall_effect.h"
#include "sd_control.h"
#include "gyroscope.h"

float current_speed;
float current_time;
float incline;
float calorie_estimate; //kcal (standard food calorie unit)
float pi = 3.14159;
float g = 9.81;
float user_mass = 70; //in kg
bool calorie_updated;

void setup() {
  
  Serial.begin(9600);
  
  sev_seg_initialise();

  sd_initialise();

  gyroscope_initialise();

  //set up interrupt service routine that is triggered by the hall effect sensor input falling edge
  pinMode(HALL_EFFECT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(HALL_EFFECT_PIN), update_current_time, FALLING);
  
}

void loop() {

  
  current_speed = calculate_speed();

  //sev_seg_set(current_speed);

  incline = getincline();
  //Serial.println(incline);

  if(calorie_updated == false) {
    calorie_estimate += estimate_calories(incline, current_speed);
    calorie_updated = true;
    Serial.println(calorie_estimate);
  }
  
 
  
  sev_seg_set(calorie_estimate);
  
  //sd_log_data(current_time, current_speed, incline, calorie_estimate);

 
}
