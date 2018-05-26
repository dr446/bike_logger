#include "hall_effect.h"

//Photoresistor Pin
float voltage_past = 0.00;
bool flip;
int flipcount = 0;
float start_time = 0.00;
float overall_time;
float currentspeed = 0.00;
float newtime;

float calculate_speed(){

// read the input on analog pin 0:
  int sensorValue = analogRead(A0);
   //delay(100);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  /* print out the value you read:
  if (voltage == 0.00) {
    Serial.println("zero");
  }
  else {
  Serial.println("non zero");
  }*/
 
  Serial.println(voltage);
  if(voltage <= 0.08) {
    if(voltage_past >= 0.08){
      flip == true;
      Serial.println("flip true");
      flipcount = flipcount + 1;
    }
    if(voltage_past <= 0.08){
      flip == false;
      //Serial.println("flip false");
    }
  }

  if(voltage >= 0.08) {
   if(voltage_past <= 0.08){
     flip == true;
     Serial.println("flip true");
     flipcount = flipcount + 1;
   }
   if(voltage_past >= 0.08){
     flip == false;
     //Serial.println("flip false");
   }
  }
   
  if (flipcount == 4) {
    flipcount = 0;
    newtime = float(now());
    currentspeed = 0.1*3.14159/(newtime-start_time);
    
    Serial.println(currentspeed); 
    Serial.print("newtime = ");
    Serial.println(newtime);
    Serial.print("Start time = ");
    Serial.println(start_time);
    start_time = float(now());
  }

  if (now()-start_time >= 10) {
    currentspeed = 0.00;
  }
  
  return(currentspeed);
  
}
