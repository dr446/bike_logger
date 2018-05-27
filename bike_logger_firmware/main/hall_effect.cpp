#include "hall_effect.h"

float prev_time;
float currentspeed;

//ISR
void update_current_time(){
  prev_time = current_time;
  current_time = float(millis())/1000;
}

float calculate_speed(){
 

  if (current_time != prev_time){
    currentspeed = 0.1*pi/(current_time-prev_time); 
  } else {
    currentspeed =0; 
  }
  
  if (millis()/1000-prev_time >= 5) {
    currentspeed = 0.00;
  }

  return(currentspeed);
  
}


