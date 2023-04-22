#pragma once


#include <esp_task_wdt.h>
#include <esp_heap_caps.h>
#include <Wire.h>

#if USE_JOYSTICK
    #include <Joystick_ESP32S2.h>
#endif

#if USE_MCP23017
    #include <Adafruit_MCP23X17.h>
#endif

#if USE_ADS1115
    ////#include <ADS1115_WE.h>
    #include <Adafruit_ADS1X15.h>
    //#include <ADS1X15.h>
#endif

#if USE_VL53L0X
    #include <Adafruit_VL53L0X.h>
#endif

//#include "libinc_joystick.h"
//#include "inc_joytick.h"
//#include "mytasks.h"
//#include "i2ctools.h"
//#include "adc_ads1115_sensor.h"
//#include "inc_mcp23017.h"
