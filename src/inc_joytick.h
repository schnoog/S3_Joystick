#include "Joystick_ESP32S2.h"
#include <esp_task_wdt.h>
#include <esp_heap_caps.h>

int UpdatedData = 0;
uint16_t valueToF = 0;
SemaphoreHandle_t xMutex = NULL;  // Create a mutex object

// Create Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_MULTI_AXIS, 128, 4,
  true, true, true, true, true, true,
  true, true, true, true, true);

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
//const bool testAutoSendMode = true;
const bool testAutoSendMode = false;


void MyButtonTest() 
{
  int sc  = 0;
  Serial.print("Button: ");
  for (int button = 0; button < 127; button++)
  {
        Serial.print(" ");
        sc++;
        if (sc > 31){
          sc = 0;
          Serial.println(button);
        }else{
          Serial.print(button);
        }
        
        
        Joystick.pressButton(button);
        Joystick.sendState();
        delay(500);
        Joystick.releaseButton(button);
        
  }
  Joystick.sendState();
}






void joystick_setup() {
  xMutex = xSemaphoreCreateMutex();
  // Set Range Values
  Joystick.setXAxisRange(0, 65535);
  Joystick.setYAxisRange(0, 65535);
  Joystick.setZAxisRange(0, 65535);
  Joystick.setRxAxisRange(0, 65535);
  Joystick.setRyAxisRange(0, 65535);
  Joystick.setRzAxisRange(0, 65535);
  Joystick.setThrottleRange(0, 65535);
  Joystick.setRudderRange(0, 65535);
  
  if (testAutoSendMode)
  {
    Joystick.begin();
  }
  else
  {
    Joystick.begin(false);
  }
  Serial.println("joystick started");

}

void joystick_loop(){
  MyButtonTest();
}

void testpress_button(int button){
              Joystick.pressButton(button);
              Joystick.sendState();
              vTaskDelay(100);
              Serial.print(".");
              Joystick.releaseButton(button);
              Joystick.sendState();
}

void joystick_infini_loop(void *pvParameters){
  int resetcount = 0;
  esp_task_wdt_init(5, false);
  esp_task_wdt_add(NULL);
  while(1){
        resetcount++;
        
        Serial.print("Btn: ");
        Serial.print(" ");
        Serial.print(resetcount);
        Serial.print(" ");
        for (int button = 0; button < 127; button++)
        {
          
                  

                  if (xSemaphoreTake (xMutex, portMAX_DELAY)) {  // take the mutex
                    //Serial.println("xmute ok");
                      testpress_button(button);
                      vTaskDelay(10);
                       xSemaphoreGive (xMutex);  // release the mutex
                  }else{
                    Serial.println("xmute failed");
                    vTaskDelay(10);
                  }
                  
                  esp_task_wdt_reset();
//                  Serial.println(esp_task_wdt_reset());
//                  heap_caps_print_heap_info(MALLOC_CAP_8BIT);                
                  //ESP.getHeapFragmentation() / ESP.getMaxFreeBlockSize()
              }
        Serial.println("");
      
        }
}

