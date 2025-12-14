#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#define LED_GPIO_R GPIO_NUM_5
#define LED_GPIO_G GPIO_NUM_22
#define LED_GPIO_B GPIO_NUM_23


typedef struct {
    int channel;
    int gpio;
    int mode;
    int timer_index;
} led_info_t;

led_info_t ledc_ch[3];


static void rgb_led_pwm_init(void)
{
    int rgb_ch;

    // red
    ledc_ch[0].channel      = LEDC_CHANNEL_0;
    ledc_ch[0].gpio         = LED_GPIO_R;
    ledc_ch[0].mode         = LEDC_HIGH_SPEED_MODE;
    ledc_ch[0].timer_index  = LEDC_TIMER_0;

    // green
    ledc_ch[1].channel      = LEDC_CHANNEL_1;
    ledc_ch[1].gpio         = LED_GPIO_G;
    ledc_ch[1].mode         = LEDC_HIGH_SPEED_MODE;
    ledc_ch[1].timer_index  = LEDC_TIMER_0;

    // blue
    ledc_ch[2].channel      = LEDC_CHANNEL_2;
    ledc_ch[2].gpio         = LED_GPIO_B;
    ledc_ch[2].mode         = LEDC_HIGH_SPEED_MODE;
    ledc_ch[2].timer_index  = LEDC_TIMER_0;

    ledc_timer_config_t ledc_timer = {
        .duty_resolution    = LEDC_TIMER_8_BIT,
        .freq_hz            = 100,
        .speed_mode         = LEDC_HIGH_SPEED_MODE,
        .timer_num          = LEDC_TIMER_0
    };
    ledc_timer_config(&ledc_timer);

    for (rgb_ch = 0; rgb_ch < 3; rgb_ch++) {
        ledc_channel_config_t ledc_channel = {
            .channel        = ledc_ch[rgb_ch].channel,
            .duty           = 0,
            .hpoint         = 0,
            .gpio_num       = ledc_ch[rgb_ch].gpio,
            .intr_type      = LEDC_INTR_DISABLE,
            .speed_mode     = ledc_ch[rgb_ch].mode,
            .timer_sel      = ledc_ch[rgb_ch].timer_index,
        };
        ledc_channel_config(&ledc_channel);
    }
}

static void rgb_led_set_color(
    uint8_t red,
    uint8_t green,
    uint8_t blue)
{
    ledc_set_duty(ledc_ch[0].mode, ledc_ch[0].channel, red);
    ledc_update_duty(ledc_ch[0].mode, ledc_ch[0].channel);

    ledc_set_duty(ledc_ch[1].mode, ledc_ch[1].channel, green);
    ledc_update_duty(ledc_ch[1].mode, ledc_ch[1].channel);

    ledc_set_duty(ledc_ch[2].mode, ledc_ch[2].channel, blue);
    ledc_update_duty(ledc_ch[2].mode, ledc_ch[2].channel);
}

static void hsv_to_rgb(
    uint16_t hue,
    uint8_t sat,
    uint8_t val,
    uint8_t *r,
    uint8_t *g,
    uint8_t *b)
{
    uint16_t region, remainder;
    uint8_t p, q, t;

    if (sat == 0) {
        *r = *g = *b = val;
        return;
    }

    region = hue / 60;
    remainder = (hue % 60) * 255 / 60;

    p = (val * (255 - sat)) / 255;
    q = (val * (255 - (sat * remainder) / 255)) / 255;
    t = (val * (255 - (sat * (255 - remainder)) / 255)) / 255;

    switch (region) {
        case 0:
            *r = val; *g = t; *b = p;
            break;
        case 1:
            *r = q; *g = val; *b = p;
            break;
        case 2:
            *r = p; *g = val; *b = t;
            break;
        case 3:
            *r = p; *g = q; *b = val;
            break;
        case 4:
            *r = t; *g = p; *b = val;
            break;
        default:
            *r = val; *g = p; *b = q;
            break;
    }
}

void app_main(void)
{
    rgb_led_pwm_init();

    printf("Rainbow LED Start\n");

    uint16_t hue = 0;
    uint8_t r, g, b;

    while (1) {
        hsv_to_rgb(hue, 255, 255, &r, &g, &b);
        rgb_led_set_color(r, g, b);

        hue = (hue + 1) % 360;
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
