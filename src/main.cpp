

//#include <HardwareSerial.h>
//#include "tasking.h"

#define USE_MUTEX
#include "libinc_joystick.h"
#include "inc_joytick.h"
#include "mytasks.h"






int loopnum = 0;


uint32_t HS = 0;
uint32_t FH = 0;
uint32_t MFH = 0;
uint32_t MAH = 0;

uint32_t CHS = 0;
uint32_t CFH = 0;
uint32_t CMFH = 0;
uint32_t CMAH = 0;






void setup(){
  static int task_number0 = 0;
  static int task_number1 = 0;
  Serial.begin(115200);
  delay(100);
  //Serial1.begin(115200);
  Serial.setDebugOutput(true);
  delay(5000);
  
  task_setup();
  joystick_setup();
  Serial.println("Starting up");
  xTaskCreate (joystick_infini_task,"Joystick Output Main Task",14500,(void*)&task_number0,1,NULL);
  xTaskCreate (joystick_run_task,"Joystick Test Task",14500,(void*)&task_number1,1,NULL);
  //xTaskCreate (joystick_infini_loop,"testloop",2500,(void*)&task_number0,1,NULL);
  //
  //joystick_loop
  HS = ESP.getHeapSize(); //total heap size
  FH = ESP.getFreeHeap(); //available heap
  MFH = ESP.getMinFreeHeap(); //lowest level of free heap since boot
  MAH = ESP.getMaxAllocHeap(); //largest block of heap that can be allocated at once


}

void loop(){
    
}

