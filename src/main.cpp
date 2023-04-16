#include <Arduino.h>
#include "settings.h"
#include "includer.h"
#include "initiator.h"


#include "func_include.h"



void setup(){
    Serial.begin(115200);
    int WF = 0;
    int PreWait = 5;
    Serial.println("Waiting");
    for (WF = 0; WF < PreWait; WF++){
        Serial.println(WF);
        delay(1000);
    }
    /*
    * Check 4 MCP I2C Adds
    */
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




    Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.begin();

    #if USE_JOYSTICK
        
    #endif
           // MCP23017_AVAILABLE[MCP_COUNT] = MCP23017_ADDRESSES[i];
            
    #if USE_MCP23017
        for (int X = 0; X < MCP_COUNT;X++){
            int BP=0;
            mcp[X].begin_I2C(MCP23017_AVAILABLE[X]);
            for(BP=0; BP < 16; BP++){
                mcp[X].pinMode(BP, INPUT_PULLUP);
                RealButtonCount++;
            }
        }
    #endif

    #if USE_ADS1115
        if(!adc.init()){
            Serial.println("ADS1115 not connected!");
            
        }else{
            adc.setVoltageRange_mV(ADS1115_RANGE_6144); 
            adc.setCompareChannels(ADS1115_COMP_0_GND);
            adc.setMeasureMode(ADS1115_CONTINUOUS);
            Serial.println("ADS1115 ready!");         

        }
    #endif

    #if USE_VL53L0X
        if (!lox.begin()) {
            Serial.println(F("Failed to boot VL53L0X"));
        }else{ 
            Serial.println(F("VL53L0X ready"));
            // task generation bla bla

        }    
    #endif








}

void loop(){
    Serial.println(PROJECTNAME);
#if USE_VL53L0X
    Serial.println(tof_getrange());
#endif
#if USE_ADS1115   
    Serial.print("ADS: ");
    Serial.print(readChannelRaw(0));
    Serial.print(" ");
    Serial.print(readChannelRaw(1));
    Serial.print(" ");
    Serial.print(readChannelRaw(2));
    Serial.print(" ");
    Serial.println(readChannelRaw(3));
    Serial.print(" ");
#endif
#if USE_MCP23017
    getMCPData();
    PrintButtons();
#endif

    delay(1000);

}