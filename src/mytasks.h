
#include "libinc_joystick.h"
#include <esp_task_wdt.h>
#include <esp_heap_caps.h>


int UpdatedData = 0;
uint16_t valueToF = 0;
SemaphoreHandle_t xMutex = NULL;  // Create a mutex object


void task_setup() {
  int mstep;
  xMutex = xSemaphoreCreateMutex();
        for(mstep =0; mstep < 128; mstep++){
          myjoy_buttons[mstep] = 0;
        }

        for(mstep =0; mstep < 2; mstep++){
          myjoy_hats[mstep] = -1;
        }
        myjoy_axis[0] = 10000;
        myjoy_axis[1]= 10000;
        myjoy_axis[2]= 10000;
        myjoy_axis[3]= 10000;
        myjoy_axis[4]= 10000;
        myjoy_axis[5]= 10000;
        myjoy_axis[6]= 10000;
}


void joystick_infini_task(void *pvParameters){
  int resetcount = 0;
  int mstep = 0;
  esp_task_wdt_init(5, false);
  esp_task_wdt_add(NULL);
  while(1){
    if (xSemaphoreTake (xMutex, portMAX_DELAY)) {  // take the mutex
        /*
        bool myjoy_buttons[ButtonNun];
        int16_t  myjoy_hats[HatNum];
        uint16_t myjoy_axis[7];
        */
        for(mstep =0; mstep < 128; mstep++){
          Joystick.setButton(mstep, myjoy_buttons[mstep]);
        }

        for(mstep =0; mstep < 2; mstep++){
          resetcount++;
          Joystick.setHatSwitch(mstep, myjoy_hats[mstep]);
        }

        
        Joystick.setXAxis(myjoy_axis[1]);
        Joystick.setYAxis(myjoy_axis[2]);
        Joystick.setZAxis(myjoy_axis[3]);
        Joystick.setRxAxis(myjoy_axis[4]);
        Joystick.setRyAxis(myjoy_axis[5]);
        Joystick.setRzAxis(myjoy_axis[6]);
        
        Joystick.setAccelerator(myjoy_axis[0]);
        Joystick.setThrottle(myjoy_axis[0]);
        Joystick.setBrake(myjoy_axis[0]);
        Joystick.setSteering(myjoy_axis[0]);
        Joystick.setRudder(myjoy_axis[0]);
        Joystick.sendState();


        vTaskDelay(1);
          xSemaphoreGive (xMutex);  // release the mutex
    }else{
      Serial.println("xmute failed");
      vTaskDelay(10);
    }                 
    esp_task_wdt_reset();
    vTaskDelay(10);
  }
     
}






void joystick_run_task(void *pvParameters){
  int resetcount = 0;
  int mstep = 0;
  long lastrun = millis();
  int lastbtn = 0;
  uint8_t lastval = 0;
  uint32_t axval =0;

  esp_task_wdt_init(5, false);
  esp_task_wdt_add(NULL);
  while(1){
    if ((millis()-lastrun)> 2000){


    if (xSemaphoreTake (xMutex, portMAX_DELAY)) {  // take the mutex
      for (mstep=0; mstep < 128 ; mstep++)
      {
        myjoy_buttons[mstep] = lastval;


      }

      for (mstep=0; mstep < 7 ; mstep++)
      {
        myjoy_axis[mstep] = axval;


      }


      if (lastval == 0){
        lastval = 1;
        axval =65535;
      }else{
        lastval = 0;
        axval = 0;
      }
      lastrun = millis();





      vTaskDelay(1);
      xSemaphoreGive (xMutex);  // release the mutex
    }else{
      Serial.println("xmute failed");
      vTaskDelay(10);
    }

    }



    esp_task_wdt_reset();
    vTaskDelay(10);
  }
     
}

