//write speed (and maybe other parameters later) to SD card from arduino

#include <SPI.h>
#include <SD.h>


void setup() {

SD_begin(9600); //Initialises communication between arduino and computer to run at 9600 bits/second


}

void loop() {

float time_unit = 0.1; //actual time needs to be put in here
float current_speed  = 5; //output from hall effect sensor calculation firmware
String data_string = "";

data_string += String(time_unit);
data_string += String(current_speed);
File dataFile = SD.open("datalog.txt", FILE_WRITE);

 if (dataFile) {
  
    dataFile.println(data_string);
    dataFile.close();

  }

}
