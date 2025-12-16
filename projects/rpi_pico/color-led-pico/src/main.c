#include <stdio.h>
#include "pico/stdlib.h"
#include "led_pwm.h"
#include "hsv.h"

int main(void)
{
    stdio_init_all();
    rgb_led_pwm_init();

    printf("Rainbow LED Start\n");

    uint16_t hue = 0;
    uint8_t r, g, b;

    while (1) {
        hsv_to_rgb(hue, 255, 255, &r, &g, &b);
        rgb_led_set_color(r, g, b);

        hue = (hue + 1) % 360;
        sleep_ms(50);
    }

    return 0;
}
