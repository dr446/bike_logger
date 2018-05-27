#include "gyroscope.h"

const int MPU_addr=0x68; 

//variables for obtaining angle
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265; 
int maxVal=402;
float x; 
float y; 
float z;

//variables for calorie counting
float MET_flat;
float MET_vert;
float MET_total;



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
  

  if (x>180){
  x = x-360.0;
  }
  if (y>180){
    y = y-360.0;
  }
  if (z>180){
    z = z-360.0;
  }

  return y;
 
}

float estimate_calories(float incline, float speed_in){

  //estimating the MET for flat ground.

    if(speed_in < 1) MET_flat = 0;
    else if (speed_in <= 8.85) MET_flat = 3.5;
    else if (8.85 < speed_in <= 15.12) MET_flat = 5.8;
    else if (15.12 < speed_in <= 19.30) MET_flat = 6.8;
    else if (19.30 < speed_in <= 22.53) MET_flat = 8;
    else if (14 < speed_in <= 25.74) MET_flat = 10;
    else if (16 < speed_in <= 32.18) MET_flat = 12;
    else if (speed_in >32.18) MET_flat = 15.8;

  //estimating the MET solely for the incline (vertical MET)

  MET_vert = g*speed_in*sin(incline);

  MET_total = MET_vert + MET_flat;
  
  //per second. This is the rate of calories burned.
  return(user_mass*MET_total);

}
