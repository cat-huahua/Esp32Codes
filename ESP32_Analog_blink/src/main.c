#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#define GPIO_NUM 2
void app_main()
{
    gpio_set_direction(GPIO_NUM, GPIO_MODE_OUTPUT);
    while (1)
    {
        gpio_set_level(GPIO_NUM, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(GPIO_NUM, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}