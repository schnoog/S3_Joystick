#pragma once
#include "settings.h"




/*
*
*/
bool IsI2CDeviceAvailable(uint8_t i2c_addr){
  bool error = true;
  bool addressFound = false;
    //Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.begin();
    delay(100);    
    Wire.beginTransmission(i2c_addr);
    error = Wire.endTransmission();
    if(error == 0){
      addressFound = true;
    }
    Wire.end();
  return addressFound;  
}


void CheckForAvailableI2CDevices(){
   bool i2cavail = false;
   for(int i=0; i <MCP23017_MAXCOUNT; i++){
        i2cavail = IsI2CDeviceAvailable(MCP23017_ADDRESSES[i]);
        if(i2cavail){

            MCP23017_AVAILABLE[MCP_COUNT] = MCP23017_ADDRESSES[i];
            MCP_COUNT++;
            Serial.print("Available: ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(MCP23017_ADDRESSES[i],HEX);
        }
    
   }
    
   for(int i=0; i <ADS1115_MAXCOUNT; i++){
        i2cavail = IsI2CDeviceAvailable(ADS1115_ADDRESSES[i]);
        if(i2cavail){

            ADS1115_AVAILABLE[ADS_COUNT] = ADS1115_ADDRESSES[i];
            ADS_COUNT++;
            Serial.print("Available: ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(ADS1115_ADDRESSES[i],HEX);
        }else{
            Serial.print(ADS1115_ADDRESSES[i],HEX);
            Serial.println(" not available");
        }   
   }
}