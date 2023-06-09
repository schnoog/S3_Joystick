#pragma once
#include "settings.h"


#if USE_JOYSTICK
    // Create Joystick
    Joystick_ Joystick(0x03, JOYSTICK_TYPE_JOYSTICK, 128, 2,
    true, true, true, true, true, true, true, true, true, true, true);
#endif

#if USE_MCP23017
    Adafruit_MCP23X17 mcp[MCP23017_MAXCOUNT] ;
#endif

#if USE_ADS1115
    Adafruit_ADS1115 adc[ADS1115_MAXCOUNT];
#endif

#if USE_VL53L0X
    Adafruit_VL53L0X lox = Adafruit_VL53L0X();
    Adafruit_VL53L0X::VL53L0X_Sense_config_t long_range = Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY;
#endif

uint8_t MCP23017_AVAILABLE[MCP23017_MAXCOUNT];
uint8_t ADS1115_AVAILABLE[ADS1115_MAXCOUNT];
int MCP_COUNT = 0;
int ADS_COUNT = 0;
int RealButtonCount = 0;
uint8_t myjoy_buttons[NUM_BUTTONS];
int16_t  myjoy_hats[NUM_HATS];
uint32_t myjoy_axis[17];  //max of 4 ads1115  + VL53



int MCPCycle = 0;
int ADSCycle = 0;
int TOFCycle = 0;


static int task_number0 = 0; // ADS1115
static int task_number1 = 0; // Joystick
static int task_number2 = 0; // MCP23017
static int task_number3 = 0; // VL53 TOF
static int task_number4 = 0;
static int task_number5 = 0;


