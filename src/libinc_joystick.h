#include "Joystick_ESP32S2.h"

#pragma once


uint8_t myjoy_buttons[128];
int16_t  myjoy_hats[2];
uint32_t myjoy_axis[7];


// Create Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 128, 2,
  true, true, true, true, true, true,
  true, true, true, true, true);

void TTest(){
  //

}
