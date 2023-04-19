#include <Arduino.h>
#include "settings.h"
#include "initiator.h"
#include "func_include.h"
#include <esp_task_wdt.h>
#include <esp_heap_caps.h>


    static int task_number0 = 0;
    //static int task_number1 = 0;

//  xTaskCreate (task_tofsensor,"Time of flight sensor task",1000,(void*)&task_number0,1,NULL);


void ADSLoop (void* pvParameters) {
    int16_t ANALOGDATA[16];
    int I;
    int Z;
    int cnt = 0;
    esp_task_wdt_init(5, false);
    esp_task_wdt_add(NULL); 
  while (1) {
    //myjoy_axis
 
    cnt = 0;
    for (I = 0; I < ADS_COUNT;I++){
        for(Z=0; Z < 4 ; Z++){
            ANALOGDATA[cnt] = readChannelRaw(Z,I);
            cnt++;
        }
        
    }

    cnt = 0;
    if (xSemaphoreTake (xMutex, portMAX_DELAY)) {  // take the mutex   
        for (I = 0; I < ADS_COUNT;I++){
            for(Z=0; Z < 4 ; Z++){
                myjoy_axis[cnt] = ANALOGDATA[cnt];
                cnt++;
            }
            
        }
      xSemaphoreGive (xMutex);  // release the mutex
    }
    esp_task_wdt_reset();
    vTaskDelay(10);    
  }
}


void RunTask_ADSLoop(){
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
xTaskCreate (ADSLoop,"Reads all available ADS1115 ADC",20000,(void*)&task_number0,1,NULL);

}