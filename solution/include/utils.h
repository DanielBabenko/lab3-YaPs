#ifndef IMAGE_TRANSFORMER_UTILS_H
#define IMAGE_TRANSFORMER_UTILS_H

#include <stdint.h>

struct image get_image(uint32_t width, uint32_t height);
static uint32_t get_paddings(uint32_t width);

#endif //IMAGE_TRANSFORMER_UTILS_H