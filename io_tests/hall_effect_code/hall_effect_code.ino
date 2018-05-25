#include <TimeLib.h>
#include <Time.h>
#include <SPI.h>
#include <SD.h>
#include "SevSeg.h"
SevSeg sevseg;

//Photoresistor Pin
int analogPin = 0;
float voltage_past = 0.00;
bool flip;
int flipcount = 0;
float start_time = 0.00;
float overall_time;
float currentspeed = 0.00;
const int chipSelect = 6;
float newtime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  start_time = now();
  overall_time = now();
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  overall_time = 0.00;

  
}

void loop() {
  // put your main code here, to run repeatedly:
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

  
 
  //Serial.println(voltage);
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
    newtime = now();
    currentspeed = 0.1*3.14159/(newtime-start_time);
    Serial.println(currentspeed); 
    Serial.print("newtime = ");
    Serial.println(newtime);
    Serial.print("Start time = ");
    Serial.println(start_time);
    start_time = now();
  }

  if (now()-start_time >= 10) {
    currentspeed = 0.00;
  }
  

//SD Card Stuff

//SD card attached to SPI bus as follows:
//MOSI - pin 11
//MISO - pin 12
//CLK - pin 13
//CS - pin 6

String time_and_speed = "";
overall_time=now();
time_and_speed = String(overall_time);
time_and_speed += ",";
time_and_speed += String(currentspeed);



// open the file. note that only one file can be open at a time,
// so you have to close this one before opening another.
File dataFile;

dataFile = SD.open("speed1.txt", FILE_WRITE);

Serial.println(dataFile);

// if the file is available, write to it:
if (dataFile) {
   dataFile.println(time_and_speed);
   dataFile.close();
   // print to the serial port too:
   Serial.println(time_and_speed);
 }
 // if the file isn't open, pop up an error:
 else {
   Serial.println("error opening speed1.txt");
 }

  voltage_past = voltage;
  sevseg.setNumber(currentspeed, 2);
}
