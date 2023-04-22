#pragma once


#define PROJECTNAME "My Super joystick project"
#define NUM_BUTTONS 128
#define NUM_AXIS 7
#define NUM_HATS 2





#define I2C_SDA 11
#define I2C_SCL 12
#define USE_MUTEX

#define USE_JOYSTICK true
#define USE_I2C true
#define USE_ADS1115 true
#define USE_MCP23017 true
#define MCP23017_MAXCOUNT 8
#define ADS1115_MAXCOUNT 4
#define USE_VL53L0X true


int16_t AIN_MIN = 0;
int16_t AIN_MAX = 65535;





#define ADS1115_I2C_ADDRESS 0x48

uint8_t MCP23017_ADDRESSES[MCP23017_MAXCOUNT] = {0x20 , 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27};
uint8_t ADS1115_ADDRESSES[ADS1115_MAXCOUNT] = {0x48 , 0x49, 0x4a, 0x4b };


SemaphoreHandle_t xMutex = NULL;  // Create a mutex object
SemaphoreHandle_t xMutexJS = NULL;  // Create a mutex object
SemaphoreHandle_t xMutexI2C = NULL;  // Create a mutex object




