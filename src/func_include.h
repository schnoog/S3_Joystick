#pragma once
#include "settings.h"


#if USE_VL53L0X
/*
* TOF Range
*/
uint16_t tof_getrange() {
    static uint16_t LastPoint;  
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    if (measure.RangeStatus != 4) { 
    LastPoint = measure.RangeMilliMeter;
    }
    return LastPoint;
}
#endif
/*
*
*/
#if USE_ADS1115
int16_t readChannelRaw(int channel) {
    int16_t rawresult = 0;
    ADS1115_MUX mimux;
    if(channel == 0) mimux = ADS1115_COMP_0_GND;  
    if(channel == 1) mimux = ADS1115_COMP_1_GND; 
    if(channel == 2) mimux = ADS1115_COMP_2_GND; 
    if(channel == 3) mimux = ADS1115_COMP_3_GND; 
    adc.setCompareChannels(mimux);
    rawresult = adc.getRawResult(); // alternative: getResult_mV for Millivolt
    if(rawresult < AIN_MIN) rawresult = AIN_MIN;
    if(rawresult > AIN_MAX) rawresult = AIN_MAX;

    return rawresult;
}
#endif


#if USE_MCP23017
/**
 * 
*/
void getMCPData(){
//myjoy_buttons
        int BTNC = 0;
        for (int X = 0; X < MCP_COUNT;X++){
            int BP=0;
            mcp[X].begin_I2C(MCP23017_AVAILABLE[X]);
            for(BP=0; BP < 16; BP++){
                myjoy_buttons[BTNC] = !mcp[X].digitalRead(BP);
                BTNC++;
            }
        }

}
#endif

/*
*
*/
bool IsI2CDeviceAvailable(uint8_t i2c_addr){
  bool error = true;
  bool addressFound = false;
    Wire.setPins(I2C_SDA, I2C_SCL);
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


void PrintButtons(){
    for (int I = 0; I < RealButtonCount; I++){
        Serial.print(myjoy_buttons[I]);
    }
    Serial.println();
}