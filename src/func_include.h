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
int16_t readChannelRaw(int channel, int SelectedADC) {
    int16_t rawresult = 0;
    ADS1115_MUX cmux;
    if(channel == 0)cmux = ADS1115_COMP_0_GND;
    if(channel == 1)cmux = ADS1115_COMP_1_GND;
    if(channel == 2)cmux = ADS1115_COMP_2_GND;
    if(channel == 3)cmux = ADS1115_COMP_3_GND;

    adc[SelectedADC].setCompareChannels(cmux);

    rawresult = adc[SelectedADC].getRawResult(); // alternative: getResult_mV for Millivolt
    //Serial.println(rawresult);
    //if(rawresult < AIN_MIN) rawresult = AIN_MIN;
    //if(rawresult > AIN_MAX) rawresult = AIN_MAX;
    return rawresult;
}

void getADSData(){
    int16_t retdata[16];
    int AIndex = 0;
    int X;
    for(X=0; X < ADS_COUNT ; X++){
    for(int i =0; i < 4 ; i++){
        AIndex = X * 4;
        AIndex += i;
        retdata[AIndex] = readChannelRaw(i,X);
    }


    }



    for(int i =0; i < 16 ; i++){
        myjoy_axis[i] = retdata[i];
    }    

}




#endif


#if USE_MCP23017
/**
 * 
*/
void getMCPData(){
//myjoy_buttons
uint8_t buttontmp[NUM_BUTTONS];
        int BTNC = 0;
        for (int X = 0; X < MCP_COUNT;X++){
            int BP=0;
            mcp[X].begin_I2C(MCP23017_AVAILABLE[X]);
            for(BP=0; BP < 16; BP++){
                buttontmp[BTNC] = !mcp[X].digitalRead(BP);
                BTNC++;
            }
        }
        for (int Y=0; Y < BTNC ;Y++){
            myjoy_buttons[Y] = buttontmp[Y];
        }



}
#endif

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


void PrintButtons(){
    for (int I = 0; I < RealButtonCount; I++){
        Serial.print(myjoy_buttons[I]);
    }
    Serial.println();
}


#if USE_JOYSTICK
void JoyStickCall(){
    int mstep;
        for(mstep =0; mstep < NUM_BUTTONS; mstep++){
          Joystick.setButton(mstep, myjoy_buttons[mstep]);
        }

        for(mstep =0; mstep < NUM_HATS; mstep++){
          Joystick.setHatSwitch(mstep, myjoy_hats[mstep]);
        }

        
        Joystick.setXAxis(myjoy_axis[1]);
        Joystick.setYAxis(myjoy_axis[2]);
        Joystick.setZAxis(myjoy_axis[3]);
        Joystick.setRxAxis(myjoy_axis[4]);
        Joystick.setRyAxis(myjoy_axis[5]);
        Joystick.setRzAxis(myjoy_axis[6]);
        Joystick.setThrottle(myjoy_axis[0]);
		
        Joystick.setAccelerator(myjoy_axis[0]);
        
        Joystick.setBrake(myjoy_axis[0]);
        Joystick.setSteering(myjoy_axis[0]);
        Joystick.setRudder(myjoy_axis[0]);
        Joystick.sendState();
}
#endif