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
float log_time;
float log_time_ref;
float current_light;
float incline;
float calorie_estimate; //kcal (standard food calorie unit)
float pi = 3.14159;
float g = 9.81;
bool calorie_updated;

//USER PARAMETERS
float user_mass = 70; //in kg
float bike_frame_incline = 46; //in degrees
float diameter = 0.7; //in meters



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
  pinMode(HALL_EFFECT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(HALL_EFFECT_PIN), update_current_time, FALLING);

  log_time_ref = millis();
  
}

void loop() {
sev_seg_set(int(current_speed*10), int(calorie_estimate*10));
  
  current_speed = calculate_speed();

  sev_seg_set(int(current_speed*10), int(calorie_estimate*10));
  
  if(calorie_updated == false) {
    incline = getincline(); 
    sev_seg_set(int(current_speed*10), int(calorie_estimate*10));
    calorie_estimate += estimate_calories(incline, current_speed);
    sev_seg_set(int(current_speed*10), int(calorie_estimate*10));
    calorie_updated = true;
    sev_seg_set(int(current_speed*10), int(calorie_estimate*10));
  }
  
  current_light = light_sense_and_check();

  sev_seg_set(int(current_speed*10), int(calorie_estimate*10));

  log_time = millis(); 
  
  if (log_time - log_time_ref>1000){
  sd_log_data(log_time/1000, current_speed, incline, calorie_estimate, current_light);    //also delay in 7 seg from calling this function
  log_time_ref = log_time;
  }
  sev_seg_set(int(current_speed*10), int(calorie_estimate*10));
 
}
