#ifndef IMAGE_TRANSFORMER_BMP_IO_H
#define IMAGE_TRANSFORMER_BMP_IO_H

#include <stdio.h>

#include "image.h"

/*  deserializer   */
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
};

enum read_status from_bmp( FILE* in, struct image* img );

/*  serializer   */
enum  write_status  {
    WRITE_OK = 0,
    WRITE_INVALID_HEADER,
    WRITE_INVALID_BITS
};

enum write_status to_bmp( FILE* out, struct image const* img );

#endif //IMAGE_TRANSFORMER_BMP_IO_H