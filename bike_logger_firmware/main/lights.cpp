#include "lights.h"

void lights_initialise() {
  pinMode(led, OUTPUT);
}

float light_sense_and_check() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);


  //setting what state light should be in
  if(voltage > 1.4){
    brightness = 0;
    analogWrite(led, brightness);
  }

  if(voltage < 1.40 and voltage > 1.2){
    brightness = 100;
    analogWrite(led, brightness);
  }
  
  if(voltage < 1.2){
    brightness = 255;
    analogWrite(led, brightness);
  }

  return voltage;
}




