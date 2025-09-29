#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define Wait 3000
void app_main(){
    while (1)
    {
        // Infinite loop to keep the application running
        printf("Hello, ESP32!\n");
        vTaskDelay(Wait / portTICK_PERIOD_MS); // Delay for 3 seconds
    }
}