#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define Wait 3000 // Wait time in milliseconds
void app_main(){
    while (1)
    {
        // Infinite loop to keep the application running
        printf("Hello, ESP32!\n");
        vTaskDelay(Wait); // Delay for 3 seconds
    }
}