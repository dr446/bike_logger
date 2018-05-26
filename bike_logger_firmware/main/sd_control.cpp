#include "sd_control.h"


//SD card attached to SPI bus as follows:
//MOSI - pin 11
//MISO - pin 12
//CLK - pin 13
//CS - pin 4


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
  Serial.println("card initialized.");
  
  Serial.end();
	
}

void sd_log_data(int time, float speed) {
	
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  
	String time_and_speed = "";
	time_and_speed = String(time);
	time_and_speed += ",";
	time_and_speed += String(speed);

  
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(time_and_speed);
    dataFile.close();
    // print to the serial port too:
    Serial.println(time_and_speed);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
	
}
