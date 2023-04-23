#pragma once
#include <Arduino.h>
#include "settings.h"
#include "initiator.h"
#include "func_include.h"
#include <esp_task_wdt.h>
#include <esp_heap_caps.h>


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
    /* initiate the available MCP23017*/
    /* all IOs as input with 100k Pull Up enabled */
        for (X = 0; X < MCP_COUNT;X++){
            BP=0;
            mcp[X].begin_I2C(MCP23017_AVAILABLE[X]);
            for(BP=0; BP < 16; BP++){
                mcp[X].pinMode(BP, INPUT_PULLUP);
                RealButtonCount++;
            }
        }

    /* mcps are initiated, let's the game begin*/


  while (1) {
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
  xTaskCreate (MCPLoop,"Reads all available MCP23017 IOs",20000,(void*)&task_number2,2,NULL);
}