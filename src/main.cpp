#include <Arduino.h>
#include "settings.h"
#include "includer.h"
#include "initiator.h"
#include "func_include.h"
#include "tasking_ads.h"
#include "tasking_joystick.h"
#include "tasking_mcp.h"
#include "tasking_tof.h"


void setup(){
    Serial.begin(115200);
    xMutex = xSemaphoreCreateMutex();
    xMutexJS = xSemaphoreCreateMutex();
    xMutexI2C = xSemaphoreCreateMutex();
#if USE_I2C
        Wire.setPins(I2C_SDA, I2C_SCL);
        CheckForAvailableI2CDevices();
        Wire.begin();
    #if USE_ADS1115
        RunTask_ADSLoop();
    #endif

    #if USE_MCP23017
        RunTask_MCPLoop();
    #endif
    #if USE_VL53L0X
        RunTask_TOFLoop();
    #endif
#endif  /* I2C enabled */
#if USE_JOYSTICK
    RunTask_JoystickLoop();
#endif


}

void loop(){

}