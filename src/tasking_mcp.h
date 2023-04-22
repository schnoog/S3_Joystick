#include <Arduino.h>
#include "settings.h"
#include "initiator.h"
#include "func_include.h"
#include <esp_task_wdt.h>
#include <esp_heap_caps.h>


    static int task_number2 = 0;
    //static int task_number1 = 0;

//  xTaskCreate (task_tofsensor,"Time of flight sensor task",1000,(void*)&task_number0,1,NULL);


void MCPLoop (void* pvParameters) {
    uint8_t buttontmp[NUM_BUTTONS];
    int I;
    int Z;
    int Y=0;
    int X = 0;
    int cnt = 0;
    int BTNC = 0;
    int BP = 0;
    esp_task_wdt_init(10, false);
    esp_task_wdt_add(NULL); 

  while (1) {
    //myjoy_axis
 
        BTNC = 0;

        for (X = 0; X < MCP_COUNT;X++){
            BP=0;
            for(BP=0; BP < 16; BP++){
                buttontmp[BTNC] = !mcp[X].digitalRead(BP);
                BTNC++;
            }
        }


      if (xSemaphoreTake (xMutex, portMAX_DELAY)) {  // take the mutex
      MCPCycle++;    
        for (Y=0; Y < BTNC ;Y++){
            myjoy_buttons[Y] = buttontmp[Y];
        }
      xSemaphoreGive (xMutex);  // release the mutex
      }

    esp_task_wdt_reset();
    vTaskDelay(5);    
  }
}


void RunTask_MCPLoop(){
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
xTaskCreate (MCPLoop,"Reads all available MCP23017 IOs",20000,(void*)&task_number2,2,NULL);

}