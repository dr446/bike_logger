//write speed (and maybe other parameters later) to SD card from arduino

#include <SPI.h>
#include <SD.h>

//SD card attached to SPI bus as follows:
//MOSI - pin 11
//MISO - pin 12
//CLK - pin 13
//CS - pin 4

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

void loop() {

String mock_data = "";

Serial.print("Initializing SD card...");

// see if the card is present and can be initialized:
if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

//load mock data from matlab and send it to SD card. This section will have to be modified to send the speed calcs from the sensors to the SD card.

while (Serial.available() == 0)
    {
    }
    if (Serial.available() > 0)
    {
      for (int i=0; i < 2 ; i++)
      {
          mock_data += string(Serial.read());
      }
      Serial.flush();
       mock_data +=",";
   }


// open the file. note that only one file can be open at a time,
// so you have to close this one before opening another.
File dataFile = SD.open("speed.txt", FILE_WRITE);

// if the file is available, write to it:
if (dataFile) {
   dataFile.println(mock_data);
   dataFile.close();
   // print to the serial port too:
   Serial.println(mock_data);
 }
 // if the file isn't open, pop up an error:
 else {
   Serial.println("error opening datalog.txt");
 }
}

}
