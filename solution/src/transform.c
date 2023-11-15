//
// Created by danie on 14.11.2023.
//

#include <malloc.h>

#include "image.h"
#include "utils.h"

struct image rotate90(struct image const source) {
    struct image destination = get_image(source.height, source.width);

    for (uint32_t row = 0; row < source.height; row++) {
        for (uint32_t col = 0; col < source.width; col++) {
            uint32_t d_row = source.width - 1 - col;
            uint32_t d_col = row;

            *(destination.data + d_row * destination.width + d_col) = *(source.data + row * source.width + col);
        }
    }
    return destination;
}

//in-place function with constant space complexity, because source and destination have the same width and height.
struct image rotate180(struct image const source) {
    for (uint32_t row = 0; row < source.height - 1 - row; row++) {
        for (uint32_t col = 0; col < source.width; col++) {
            uint32_t d_row = source.height - 1 - row;
            uint32_t d_col = source.width - 1 - col;

            //swap pixels
            struct pixel tmp = *(source.data + d_row * source.width + d_col);
            *(source.data + d_row * source.width + d_col) = *(source.data + row * source.width + col);
            *(source.data + row * source.width + col) = tmp;
        }
    }
    return source;
}

struct image rotate270(struct image const source) {
    struct image destination = get_image(source.height, source.width);

    for (uint32_t row = 0; row < source.height; row++) {
        for (uint32_t col = 0; col < source.width; col++) {
            uint32_t d_row = col;
            uint32_t d_col = source.height - 1 - row;
            *(destination.data + d_row * destination.width + d_col) = *(source.data + row * source.width + col);
        }
    }

    return destination;
}