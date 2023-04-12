

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
  tof_setup();  
  task_setup();
  joystick_setup();

  Serial.println("Starting up");
  xTaskCreate (joystick_infini_task,"Joystick Output Main Task",14500,(void*)&task_number0,1,NULL);
  xTaskCreate (joystick_run_task,"Joystick Test Task",14500,(void*)&task_number1,1,NULL);
  xTaskCreate (joystick_run_tof_task,"Joystick TimeOfFlight Task",2500,(void*)&task_number1,1,NULL);
  //xTaskCreate (joystick_infini_loop,"testloop",2500,(void*)&task_number0,1,NULL);
  //
  //joystick_loop
  HS = ESP.getHeapSize(); //total heap size
  FH = ESP.getFreeHeap(); //available heap
  MFH = ESP.getMinFreeHeap(); //lowest level of free heap since boot
  MAH = ESP.getMaxAllocHeap(); //largest block of heap that can be allocated at once


}



void scanI2C(long frequency){
  String normal = "standard mode (100 kHz):";
  String fast = "fast mode (400 kHz):";
  String fastPlus = "fast mode plus (1 MHz):";
  String highSpeed = "high speed mode (3.4 MHz):";
  String ultraSpeed = "ultra fast mode (5.0 MHz):";
  String defaultStr = " !!!!! Unzulässige Frequenz !!!!!";
  bool error = true;
  bool addressFound = false;
  Serial.print("Scanne im ");
  switch(frequency){
    case 100000:
      Serial.println(normal);
      break;
    case 400000:
      Serial.println(fast);
      break;
    case 1000000:
      Serial.println(fastPlus);
      break;
    case 3400000:
      Serial.println(highSpeed);
      break;
    case 5000000:
      Serial.println(ultraSpeed);
      break;
    default:
      Serial.println(defaultStr);
      break;
  }
  
  Wire.setClock(frequency);
  for(int i=1; i<128; i++){
    Wire.beginTransmission(i);
    error = Wire.endTransmission();
    if(error == 0){
      addressFound = true;
      Serial.print("0x");
      Serial.println(i,HEX);
    }
  }
  if(!addressFound){
    Serial.println("Keine Adresse erkannt");
  }
  Serial.println();
}







void loop(){
//    uint16_t Mess = tof_getrange();
//    Serial.println(Mess);
    delay (1);
}

