#include "sd_control.h"


//SD card attached to SPI bus as follows:
//MOSI - pin 11
//MISO - pin 12
//CLK - pin 13
//CS - pin 7


void sd_initialise(){
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  SD.remove("datalog2.csv");
  Serial.println("card initialized.");
  
  //Serial.end();
	
}

void sd_log_data(int time_in, float speed_in, float incline, float calories, float light) {
  
  File dataFile = SD.open("datalog2.csv", FILE_WRITE);
  
	String time_and_speed = "";
	time_and_speed = String(time_in);
	time_and_speed += ",";
	time_and_speed += String(speed_in);
  time_and_speed += ",";
  time_and_speed += String(incline);
  time_and_speed += ",";
  time_and_speed += String(calories);
  time_and_speed += ",";
  time_and_speed += String(light);
  
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(time_and_speed);
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
	
}
