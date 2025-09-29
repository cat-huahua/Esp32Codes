#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#define LED_GPIO 2
int Input;
void app_main()
{
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
    while (1)
    {
        scanf("%d", &Input);
        if (Input)
        {
            gpio_set_level(LED_GPIO, 1);
        }
        else
        {
            gpio_set_level(LED_GPIO, 0);
        }
        
    }
}