#include <Wire.h>
#include "Arduino.h"
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp1;
Adafruit_MCP23008 mcp2;
Adafruit_MCP23008 mcp3;

uint8_t segment_code(int number);
uint8_t digit_code(uint8_t digit_disp);

void setup() {
  
  mcp1.begin(0);
  mcp2.begin(1);
  mcp3.begin(7);

  for (int i = 0 ; i<8; i++){
  mcp1.pinMode(i, OUTPUT);
  mcp2.pinMode(i, OUTPUT);
  mcp3.pinMode(i, OUTPUT);
  }
}

void loop() {

  int num_top = 4361;
  int num_bot = 2459;
  int ones = num_top % 10;
  int tens = (num_top/10) % 10;
  int huns = (num_top/100) % 10;
  int thous = (num_top/1000) % 10;
  
  mcp1.writeGPIO(segment_code(10));
  mcp3.writeGPIO(segment_code(10));
  mcp2.writeGPIO(digit_code(3));
  mcp1.writeGPIO(segment_code(num_top % 10));
  mcp3.writeGPIO(add_dp(segment_code(num_bot % 10)));
  delay(5);
  mcp1.writeGPIO(segment_code(10));
  mcp3.writeGPIO(segment_code(10));
  mcp2.writeGPIO(digit_code(2));
  mcp1.writeGPIO(add_dp(segment_code(tens)));
  mcp3.writeGPIO(segment_code((num_bot/10)%10));
  delay(5);
  mcp1.writeGPIO(segment_code(10));
  mcp3.writeGPIO(segment_code(10));
  mcp2.writeGPIO(digit_code(1));
  mcp1.writeGPIO(segment_code(huns));
  mcp3.writeGPIO(segment_code(huns));
  delay(5);
  mcp1.writeGPIO(segment_code(10));
  mcp3.writeGPIO(segment_code(10));
  mcp2.writeGPIO(digit_code(0));
  mcp1.writeGPIO(segment_code(thous));
  mcp3.writeGPIO(segment_code(thous));
  delay(5);
}

uint8_t segment_code(int number){
 switch(number){
   case 0: return 0b10100000; break;
   case 1: return 0b10111011; break;
   case 2: return 0b01100010; break;
   case 3: return 0b00101010; break;
   case 4: return 0b00111001; break;
   case 5: return 0b00101100; break;
   case 6: return 0b00100100; break;
   case 7: return 0b00111010; break;
   case 8: return 0b00100000; break;
   case 9: return 0b00111000; break;
   default: return 0b11111111; break;
 }
}

uint8_t add_dp(uint8_t seg_code) {
  
    return seg_code - 32;
  }

uint8_t digit_code(uint8_t digit_disp){
  uint8_t temp = (1 << digit_disp);
  return temp |= temp << 4;
}

