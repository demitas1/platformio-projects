#include "led_pwm.h"
#include <Arduino.h>

void rgb_led_pwm_init(void)
{
    pinMode(LED_PIN_R, OUTPUT);
    pinMode(LED_PIN_G, OUTPUT);
    pinMode(LED_PIN_B, OUTPUT);

    // Initialize all LEDs to off
    analogWrite(LED_PIN_R, 0);
    analogWrite(LED_PIN_G, 0);
    analogWrite(LED_PIN_B, 0);
}

void rgb_led_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    analogWrite(LED_PIN_R, red);
    analogWrite(LED_PIN_G, green);
    analogWrite(LED_PIN_B, blue);
}
