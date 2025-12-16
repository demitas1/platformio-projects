#ifndef HSV_H
#define HSV_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void hsv_to_rgb(uint16_t hue, uint8_t sat, uint8_t val,
                uint8_t *r, uint8_t *g, uint8_t *b);

#ifdef __cplusplus
}
#endif

#endif
