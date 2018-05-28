#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <TimeLib.h>
#include <Time.h>
#include "sev_seg_initialise.h"
#include "hall_effect.h"
#include "sd_control.h"
#include "gyroscope.h"
#include "lights.h"


//speed and calorie calculation setup
float current_speed;
float current_time;
float current_light;
float incline;
float calorie_estimate; //kcal (standard food calorie unit)
float pi = 3.14159;
float g = 9.81;
float user_mass = 70; //in kg
bool calorie_updated;


//light set up
int led = 9;
int brightness = 0;

void setup() {
  
  Serial.begin(9600);
  
  sev_seg_initialise();

  sd_initialise();

  gyroscope_initialise();

  lights_initialise();

  //set up interrupt service routine that is triggered by the hall effect sensor input falling edge
  pinMode(HALL_EFFECT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(HALL_EFFECT_PIN), update_current_time, FALLING);
  
}

void loop() {

  
  current_speed = calculate_speed();
  
  sev_seg_set(calorie_estimate,1);
  
  //sev_seg_set(current_speed,2);

  incline = getincline();           //delay  in 7 seg from calling this function
  //Serial.println(incline);

  sev_seg_set(calorie_estimate,1);

  if(calorie_updated == false) {
    calorie_estimate += estimate_calories(incline, current_speed);
    calorie_updated = true;
    Serial.println(calorie_estimate);
  }
  sev_seg_set(calorie_estimate,1);
  current_light = light_sense_and_check();
  
  sev_seg_set(calorie_estimate,1);

  
  sd_log_data(millis()/1000, current_speed, incline, calorie_estimate, current_light);    //also delay in 7 seg from calling this function

  sev_seg_set(calorie_estimate,1);
 
}
