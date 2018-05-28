#include "gyroscope.h"

const int MPU_addr=0x68; 

//variables for obtaining angle
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265; 
int maxVal=402;
float x; 
float y; 
float z;


void gyroscope_initialise(){

  Wire.begin(); 
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);
  
}

float getincline(){
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr,14,true); 
  AcX=Wire.read()<<8|Wire.read(); 
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read(); 
  int xAng = map(AcX,minVal,maxVal,-90,90); 
  int yAng = map(AcY,minVal,maxVal,-90,90); 
  
  int zAng = map(AcZ,minVal,maxVal,-90,90);
  
  //we are interested in angle y. 0 when horizontal. All three angles are calculated in case the hardware layout is changed later.
  x= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI); 
  y= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); 
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  

  //normalise to correct range
  if (x>180){
  x = x-360.0;
  }
  if (y>180){
    //Serial.println(y);
    y = y-360.0; 
  }
  if (z>180){
    z = z-360.0;
  }

  //don't burn calories if you're going downhill
  if(y<0) {
    //Serial.println("yang1");
    //Serial.println(y);
    return 0;
  }

 //Serial.println("y is ");
 //Serial.print(y);
  
  if (y>0){
    //Serial.print("yang2");
    //Serial.println(y);
    return y;
  }
}


