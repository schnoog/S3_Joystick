#include "Joystick_ESP32S2.h"

// Create Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 128, 4,
  true, true, true, true, true, true,
  true, true, true, true, true);

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
//const bool testAutoSendMode = true;
const bool testAutoSendMode = false;


void MyButtonTest() 
{
  for (int button = 0; button < 127; button++)
  {
        Serial.print("Press button");
        Serial.println(button);
        Joystick.pressButton(button);
        Joystick.sendState();
        delay(500);
        Serial.print("Release button");
        Serial.println(button);
        Joystick.releaseButton(button);
        
  }
  Joystick.sendState();
}






void joystick_setup() {

  // Set Range Values
  Joystick.setXAxisRange(0, 65535);
  Joystick.setYAxisRange(0, 65535);
  Joystick.setZAxisRange(0, 65535);
  Joystick.setRxAxisRange(0, 65535);
  Joystick.setRyAxisRange(0, 65535);
  Joystick.setRzAxisRange(0, 65535);
  Joystick.setThrottleRange(0, 65535);
  Joystick.setRudderRange(0, 65535);
  
  if (testAutoSendMode)
  {
    Joystick.begin();
  }
  else
  {
    Joystick.begin(false);
  }
  Serial.println("joystick started");

}

void joystick_loop(){
  MyButtonTest();
}