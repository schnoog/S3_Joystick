#pragma once
#include <Arduino.h>
#include "settings.h"
#include "initiator.h"
#include "func_include.h"
#include <esp_task_wdt.h>
#include <esp_heap_caps.h>


void TOFLoop (void* pvParameters) {
    uint16_t ANALOGDATA;
    int I;
    int Z;
    int cnt = 0;
    /* initiate the VL53 */
        if (!lox.begin()) {
            Serial.println(F("Failed to boot VL53L0X"));
        }else{ 
            Serial.println(F("VL53L0X ready"));
            lox.setMeasurementTimingBudgetMicroSeconds(200000);
            lox.startRangeContinuous();
        }
    /* tof sensor initiated, let's the game begin*/
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
  xTaskCreate (TOFLoop,"Read the VL53 time of flight sensor",20000,(void*)&task_number3,10,NULL);
}