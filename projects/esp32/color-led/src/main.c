#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO_R GPIO_NUM_5
#define LED_GPIO_G GPIO_NUM_22
#define LED_GPIO_B GPIO_NUM_23

void app_main(void)
{
    // GPIO設定
    gpio_reset_pin(LED_GPIO_R);
    gpio_reset_pin(LED_GPIO_G);
    gpio_reset_pin(LED_GPIO_B);
    gpio_set_direction(LED_GPIO_R, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GPIO_G, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GPIO_B, GPIO_MODE_OUTPUT);

    printf("LED Blink Start\n");

    while (1) {
        gpio_set_level(LED_GPIO_R, 1);
        printf("LED RED ON\n");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_GPIO_R, 0);
        printf("LED RED OFF\n");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_GPIO_G, 1);
        printf("LED GREEN ON\n");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_GPIO_G, 0);
        printf("LED GREEN OFF\n");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_GPIO_B, 1);
        printf("LED BLUE ON\n");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED_GPIO_B, 0);
        printf("LED BLUE OFF\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
