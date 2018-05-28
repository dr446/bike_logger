#include "hall_effect.h"

float prev_time;
float currentspeed;
float diameter = 0.1;

//variables for calorie counting
float MET_flat;
float MET_vert;
float MET_total;
float Calories;
float calorie_norm = (1.0/3600.0);

//ISR
void update_current_time(){
  calorie_updated = false;
  prev_time = current_time;
  current_time = float(millis())/1000;
  Serial.println("isr entered");
  Serial.println(currentspeed);
}

float calculate_speed(){
 

  if (current_time != prev_time){
    currentspeed = (diameter/4)*pi/(current_time-prev_time); 
  } else {
    currentspeed =0; 
  }
  
  if (millis()/1000-prev_time >= 5) {
    currentspeed = 0.00;
  }

  //convert from ms^-1 to kmh^-1
  currentspeed = currentspeed*3.6;
  
  return(currentspeed);
  
}

float estimate_calories(float incline, float speed_in){

  //estimating the MET for flat ground.

    if(speed_in < 1) MET_flat = 0;
    else if (speed_in <= 8.85) MET_flat = 3.5;
    else if (8.85 < speed_in <= 15.12) MET_flat = 5.8;
    else if (15.12 < speed_in <= 19.30) MET_flat = 6.8;
    else if (19.30 < speed_in <= 22.53) MET_flat = 8;
    else if (14 < speed_in <= 25.74) MET_flat = 10;
    else if (16 < speed_in <= 32.18) MET_flat = 12;
    else if (speed_in >32.18) MET_flat = 15.8;

  //estimating the MET solely for the incline (vertical MET)

  MET_vert = 0.000239006*g*speed_in*sin(incline*(pi/180));
  //MET_vert = g*speed_in*sin(incline*(pi/180));

  MET_total = MET_vert + MET_flat;
  //Serial.println("vertical cals");
  //Serial.println(MET_vert);

  //Serial.println(calorie_norm);
  
  Calories = MET_total * (current_time - prev_time) * user_mass * calorie_norm;
  
  //per second. This is the rate of calories burned.
  return(Calories);

}
