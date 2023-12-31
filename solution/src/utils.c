//
// Created by danie on 14.11.2023.
//
#include <malloc.h>

#include "handle_errors.h"
#include "image.h"
#include "utils.h"

struct image get_image(uint32_t width, uint32_t height) {
    struct image img;
    img.width = width;
    img.height = height;
    img.data = malloc(width * height * sizeof(struct pixel));

    if (img.data == NULL) {
        handle_out_of_memory_error();
    }

    return img;
}