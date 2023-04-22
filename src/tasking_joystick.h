#include <Arduino.h>
#include "settings.h"
#include "initiator.h"
#include "func_include.h"
#include <esp_task_wdt.h>
#include <esp_heap_caps.h>


    //static int task_number0 = 0;
    static int task_number1 = 0;

//  xTaskCreate (task_tofsensor,"Time of flight sensor task",1000,(void*)&task_number0,1,NULL);


void JoystickLoop (void* pvParameters) {
  int mstep;
  int i;
  int updated=0;
  long outputtrigger = 0;
  int AC= 0;
  int MC = 0;
  int TC =0;
  long lastrun = millis();
  int printafter = 200;
    esp_task_wdt_init(5, false);
    esp_task_wdt_add(NULL); 
  while (1) {
      if (xSemaphoreTake (xMutex, portMAX_DELAY)) {  // take the mutex   
        for(mstep =0; mstep < NUM_BUTTONS; mstep++){
            Joystick.setButton(mstep, myjoy_buttons[mstep]);
          }

          for(mstep =0; mstep < NUM_HATS; mstep++){
            Joystick.setHatSwitch(mstep, myjoy_hats[mstep]);
          }
      outputtrigger++;
      Joystick.setXAxis(myjoy_axis[1]);
      Joystick.setYAxis(myjoy_axis[2]);
      Joystick.setZAxis(myjoy_axis[3]);
      Joystick.setRxAxis(myjoy_axis[4]);
      Joystick.setRyAxis(myjoy_axis[5]);
      Joystick.setRzAxis(myjoy_axis[6]);
      Joystick.setThrottle(myjoy_axis[0]);


      Joystick.setAccelerator(myjoy_axis[0]);        
      Joystick.setBrake(myjoy_axis[0]);
      Joystick.setSteering(myjoy_axis[0]);
      Joystick.setRudder(myjoy_axis[0]);
      Joystick.sendState();
      updated++;



      xSemaphoreGive (xMutex);  // release the mutex


      if(outputtrigger > printafter -1){
        if (xSemaphoreTake (xMutex, portMAX_DELAY)) {  // take the mutex    
              TC = TOFCycle;
              TOFCycle=0;
              MC = MCPCycle;
              MCPCycle =0;
              AC = ADSCycle;
              ADSCycle = 0;
        xSemaphoreGive (xMutex);  // release the mutex
        }
          Serial.print(printafter);
          Serial.print(" joystick cycles - j/mcp/ads/tof ");
          Serial.print(updated);Serial.print("/");Serial.print(MC);Serial.print("/");
          Serial.print(AC);Serial.print("/");Serial.print(TC);          
          Serial.print(" Joystick updates in (ms): ");
          Serial.println( (millis()-lastrun) );
          for(i=0;i<17;i++){
          Serial.print(myjoy_axis[i]);
          Serial.print(" / ");
          }
          Serial.println("");
          for(i=0; i < RealButtonCount; i++){
            Serial.print(myjoy_buttons[i]);
          }
          Serial.println("");
          outputtrigger = 0;
          updated = 0;
          lastrun = millis();
      }
      esp_task_wdt_reset();
      vTaskDelay(5);

    }    
  }
}


void RunTask_JoystickLoop(){
  /*
  xTaskCreatePinnedToCore (
    ADSLoop,     // Function to implement the task
    "Reading out the connected ADS1115 devices",   // Name of the task
    20000,      // Stack size in words
    NULL,      // Task input parameter
    10,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );
*/
xTaskCreate (JoystickLoop,"Puts the data into the joystick object",20000,(void*)&task_number0,1,NULL);

}