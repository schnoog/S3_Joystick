#include <Arduino.h>
#include "settings.h"
#include "initiator.h"
#include "func_include.h"
#include <esp_task_wdt.h>
#include <esp_heap_caps.h>


    static int task_number3 = 0;
    //static int task_number1 = 0;

//  xTaskCreate (task_tofsensor,"Time of flight sensor task",1000,(void*)&task_number0,1,NULL);


void TOFLoop (void* pvParameters) {
    uint16_t ANALOGDATA;
    int I;
    int Z;
    int cnt = 0;
    esp_task_wdt_init(5, false);
    esp_task_wdt_add(NULL); 
  while (1) {
    //myjoy_axis
 
    cnt = 0;
    vTaskDelay(1);
    if (lox.isRangeComplete()) {
      ANALOGDATA = lox.readRange();
      cnt = 0;
      if (xSemaphoreTake (xMutex, portMAX_DELAY)) {  // take the mutex   
        TOFCycle++;
                  myjoy_axis[16] = ANALOGDATA;           
        xSemaphoreGive (xMutex);  // release the mutex
      }
    }else{
      vTaskDelay(50);
    }
      esp_task_wdt_reset();
      vTaskDelay(50);    
  }
}


void RunTask_TOFLoop(){
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
xTaskCreate (TOFLoop,"Read the VL53 time of flight sensor",20000,(void*)&task_number3,10,NULL);

}