#pragma once
#include "settings.h"


#if USE_JOYSTICK
    // Create Joystick
    Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS, 128, 2,
    true, true, true, true, true, true, true, true, true, true, true);
#endif

#if USE_MCP23017
    Adafruit_MCP23X17 mcp[MCP23017_MAXCOUNT] ;
#endif

#if USE_ADS1115
    ADS1115_WE adc = ADS1115_WE(ADS1115_I2C_ADDRESS);
#endif

#if USE_VL53L0X
    Adafruit_VL53L0X lox = Adafruit_VL53L0X();
    Adafruit_VL53L0X::VL53L0X_Sense_config_t long_range = Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY;
#endif

uint8_t MCP23017_AVAILABLE[MCP23017_MAXCOUNT];
int MCP_COUNT = 0;
int RealButtonCount = 0;
uint8_t myjoy_buttons[NUM_BUTTONS];
int16_t  myjoy_hats[NUM_HATS];
uint32_t myjoy_axis[NUM_AXIS];


