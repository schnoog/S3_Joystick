#include "inc_joytick.h"


void setup(){
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  joystick_setup();
}


void loop(){
  joystick_loop();
}
