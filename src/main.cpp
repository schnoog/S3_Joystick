#include <Arduino.h>
#include "settings.h"
#include "includer.h"
#include "initiator.h"
#include "func_include.h"
#include "tasking_ads.h"
#include "tasking_joystick.h"


void setup(){
    Serial.begin(115200);
    xMutex = xSemaphoreCreateMutex();
    xMutexJS = xSemaphoreCreateMutex();
    xMutexI2C = xSemaphoreCreateMutex();
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
   #if USE_I2C
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


    //Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.setClock(20000);
    Wire.begin();
    #endif
    #if USE_JOYSTICK
        Joystick.setXAxisRange(0, 65535);
        Joystick.setYAxisRange(0, 65535);
        Joystick.setZAxisRange(0, 65535);
        Joystick.setRxAxisRange(0, 65535);
        Joystick.setRyAxisRange(0, 65535);
        Joystick.setRzAxisRange(0, 65535);
        Joystick.setThrottleRange(0, 65535);
        Joystick.setRudderRange(0, 65535);
        Joystick.setAcceleratorRange(0,65535);
        Joystick.setSteeringRange(0,65535);
        Joystick.setBrakeRange(0,65535);
        Joystick.begin(false); // no auto send
        Serial.println("joystick started");
        int mstep;
        delay(50);
        for(mstep =0; mstep < NUM_BUTTONS; mstep++){
          myjoy_buttons[mstep] = 0;
        }

        for(mstep =0; mstep < NUM_HATS; mstep++){
          myjoy_hats[mstep] = -1;
        }
        for(mstep =0; mstep < NUM_AXIS; mstep++){
          myjoy_axis[mstep] = 12345;
        }

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
            for (int X = 0; X < ADS_COUNT;X++){
                adc[X] = ADS1115_WE(ADS1115_AVAILABLE[X]);
                Serial.print(ADS_COUNT);
                Serial.println(" ads 1115 available");
                if(!adc[X].init(  )){
                    Serial.println("ADS1115 not connected!");
                    
                }else{
                    adc[X].setCompareChannels(ADS1115_COMP_0_GND);
                    adc[X].setVoltageRange_mV(ADS1115_RANGE_4096);
                    adc[X].setMeasureMode(ADS1115_CONTINUOUS);
                    
                    Serial.println("ADS1115 ready!");         
                    //RunTask_ADSLoop();
                }


            }




    #endif

    #if USE_VL53L0Xs
        if (!lox.begin()) {
            Serial.println(F("Failed to boot VL53L0X"));
        }else{ 
            Serial.println(F("VL53L0X ready"));
            // task generation bla bla

        }    
    #endif



#if USE_ADS1115
    RunTask_ADSLoop();
#endif
#if USE_JOYSTICK
    RunTask_JoystickLoop();
#endif



}

void loop(){
    Serial.println(PROJECTNAME);
#if USE_VL53L0Xx
    Serial.println(tof_getrange());
#endif
#if USE_ADS1115XX   
    Serial.print("ADS: ");
    Serial.print(readChannelRaw(0,0));
    Serial.print(" ");
    Serial.print(readChannelRaw(1,0));
    Serial.print(" ");
    Serial.print(readChannelRaw(2,0));
    Serial.print(" ");
    Serial.println(readChannelRaw(3,0));
    Serial.print(" ");
#endif
#if USE_MCP23017x
    getMCPData();
    PrintButtons();
#endif
#if USE_JOYSTICK
   // JoyStickCall();
#endif
    delay(500);

}