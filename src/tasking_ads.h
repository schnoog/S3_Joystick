#pragma once
#include <Arduino.h>
#include "settings.h"
#include "initiator.h"
#include "func_include.h"
#include <esp_task_wdt.h>
#include <esp_heap_caps.h>



void ADSLoop (void* pvParameters) {
  double FilterLimit = 0.1;
  Ewma adcFilter[16] = {
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit),
(FilterLimit)
};
  int16_t ANALOGDATA[16];
  int I;
  int Z;
  int cnt = 0;
  int X = 0;

  /* Initiate all available ADS1115*/
  for (X = 0; X < ADS_COUNT;X++){
      Serial.print(ADS_COUNT);
      Serial.println(" ads 1115 available");
      adc[X].setGain(GAIN_ONE);
      adc[X].setDataRate(RATE_ADS1115_860SPS);
      if(!adc[X].begin( ADS1115_AVAILABLE[X] )){
          Serial.println("ADS1115 not connected!");                    
      }else{                   
          Serial.println("ADS1115 ready!");         
      }
  }
  /* now that all ads are initiated, let's the game begin */
  esp_task_wdt_init(5, false);
  esp_task_wdt_add(NULL); 
  while (1) {
    cnt = 0;
    vTaskDelay(1);
    for (I = 0; I < ADS_COUNT;I++){
        for(Z=0; Z < 4 ; Z++){
        ANALOGDATA[cnt] = (int16_t) adcFilter[cnt].filter(adc[I].readADC_SingleEnded(Z));


//          ANALOGDATA[cnt] = adc[I].readADC_SingleEnded(Z);
          cnt++;
        }       
    }
    //vTaskDelay(1);
    cnt = 0;
    if (xSemaphoreTake (xMutex, portMAX_DELAY)) {  // take the mutex  
      ADSCycle++; 
      for (I = 0; I < ADS_COUNT;I++){
        for(Z=0; Z < 4 ; Z++){
          myjoy_axis[cnt] = ANALOGDATA[cnt];
          cnt++;
        }
      }
      xSemaphoreGive (xMutex);  // release the mutex
    }
    esp_task_wdt_reset();
    vTaskDelay(2);    
  }
}


void RunTask_ADSLoop(){
  xTaskCreate (ADSLoop,"Reads all available ADS1115 ADC",20000,(void*)&task_number0,2,NULL);
}