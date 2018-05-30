#include "sev_seg_initialise.h"

SevSeg sevenseg; //Instantiate a seven segment controller object

void sev_seg_initialise(){

  byte numDigits = 4;
  byte digitPins[] = {0,1,2,3};
  byte segmentPins[] = {0, 1, 2, 3, 4, 5, 6, 7};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_ANODE;
  bool updateWithDelays = false;
  bool leadingZeros = false;
  bool i2c = true;
  
  
  sevenseg.begin(i2c, hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevenseg.setBrightness(100);
  
}

void sev_seg_set(int display, float speed, int digits){
  
  sevenseg.setNumber(display, speed, digits);
  sevenseg.refreshDisplay(display);
  
}

