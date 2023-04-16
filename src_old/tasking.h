
#define USE_MUTEX
#include <esp_task_wdt.h>
#include <esp_heap_caps.h>

int UpdatedData = 0;
uint16_t valueToF = 0;
SemaphoreHandle_t xMutex = NULL;  // Create a mutex object

