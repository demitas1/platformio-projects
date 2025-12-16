#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include "led_pwm.h"
#include "hsv.h"

void vRainbowTask(void *pvParameters)
{
    uint16_t hue = 0;
    uint8_t r, g, b;

    while (1) {
        hsv_to_rgb(hue, 255, 255, &r, &g, &b);
        rgb_led_set_color(r, g, b);

        hue = (hue + 1) % 360;
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println("Rainbow LED Start");

    rgb_led_pwm_init();

    xTaskCreate(
        vRainbowTask,
        "Rainbow",
        256,
        NULL,
        1,
        NULL
    );
}

void loop()
{
    vTaskDelay(pdMS_TO_TICKS(1000));
}
