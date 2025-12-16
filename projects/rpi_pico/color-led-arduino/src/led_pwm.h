#ifndef LED_PWM_H
#define LED_PWM_H

#include <stdint.h>

// GPIO pin definitions for RGB LED
// Change these values according to your hardware setup
#ifndef LED_PIN_R
#define LED_PIN_R 10
#endif

#ifndef LED_PIN_G
#define LED_PIN_G 14
#endif

#ifndef LED_PIN_B
#define LED_PIN_B 15
#endif

void rgb_led_pwm_init(void);
void rgb_led_set_color(uint8_t red, uint8_t green, uint8_t blue);

#endif
