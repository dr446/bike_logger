#include "sev_seg_initialise.h"

SevSeg sevenseg; //Instantiate a seven segment controller object

void sev_seg_initialise(){

  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {0, 1, 2, 3, 4, 5, 6, 7};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_ANODE;
  bool updateWithDelays = false;
  bool leadingZeros = false;
  
  sevenseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevenseg.setBrightness(100);
  
}

void sev_seg_set(float speed){

  sevenseg.setNumber(speed, 2);
  sevenseg.refreshDisplay();
  
}

