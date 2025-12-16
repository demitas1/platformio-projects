#include "led_pwm.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

static void pwm_init_pin(uint gpio)
{
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice, 255);
    pwm_set_enabled(slice, true);
}

void rgb_led_pwm_init(void)
{
    pwm_init_pin(LED_PIN_R);
    pwm_init_pin(LED_PIN_G);
    pwm_init_pin(LED_PIN_B);

    // Initialize all LEDs to off
    rgb_led_set_color(0, 0, 0);
}

void rgb_led_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    pwm_set_gpio_level(LED_PIN_R, red);
    pwm_set_gpio_level(LED_PIN_G, green);
    pwm_set_gpio_level(LED_PIN_B, blue);
}
