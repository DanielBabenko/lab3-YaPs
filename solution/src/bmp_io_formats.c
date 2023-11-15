#include <stdio.h>

#include "bmp_io_formats.h"
#include "image.h"
#include "utils.h"

#define BMP_TYPE 19778
#define BF_RESERVED 0
#define BI_SIZE 40          // 54 (size of Full Header) - 14 (size of BitMapFileHeader)
#define BI_PLANES 1
#define BI_COMPRESSION 0
#define BI_X_PIXELS_PER_METER 0
#define BI_Y_PIXELS_PER_METER 0
#define BI_CLR_USED 0
#define BI_CLR_IMPORTANT 0

#define BITS_IN_BYTE 8

struct __attribute__((packed)) bmp_header {
uint16_t bfType;
uint32_t  bfileSize;
uint32_t bfReserved;
uint32_t bOffBits;
uint32_t biSize;
uint32_t biWidth;
uint32_t  biHeight;
uint16_t  biPlanes;
uint16_t biBitCount;
uint32_t biCompression;
uint32_t biSizeImage;
uint32_t biXPelsPerMeter;
uint32_t biYPelsPerMeter;
uint32_t biClrUsed;
uint32_t  biClrImportant;
};

static uint32_t get_paddings(uint32_t width){
    uint32_t row = width * sizeof(struct pixel);
    uint32_t paddings = 4 - (row % 4);
    if (paddings == 4){
        paddings = 0;
    }
    return paddings;
}

/*  deserializer   */
enum read_status from_bmp(FILE *in, struct image *img) {
    if (img == NULL) {
        return READ_INVALID_BITS;
    }

    struct bmp_header header;

    size_t count = fread(&header, sizeof(struct bmp_header), 1, in);

    if (count != 1) {
        return READ_INVALID_HEADER;
    }

    if (header.bfType != BMP_TYPE) {
        return READ_INVALID_SIGNATURE;
    }

    *img = get_image(header.biWidth, header.biHeight);

    for (uint32_t row = 0; row < img->height; row++) {

        count = fread(img->data + row * img->width, sizeof(struct pixel), img->width, in);

        if (count != img->width) {
            return READ_INVALID_BITS;
        }
        //skip padding
        fseek(in, (long) get_paddings(img->width), SEEK_CUR);
    }

    return READ_OK;
}

struct bmp_header get_header(uint32_t width, uint32_t height) {
    struct bmp_header header;

    header.bfType = BMP_TYPE;

    header.bfileSize = sizeof(struct bmp_header) +
                       height * (width * sizeof(struct pixel) + get_paddings(width));

    header.bfReserved = BF_RESERVED;
    header.bOffBits = sizeof(struct bmp_header);        //54

    header.biSize = BI_SIZE;     //size of information header
    header.biWidth = width;
    header.biHeight = height;
    header.biPlanes = BI_PLANES;
    header.biBitCount = sizeof(struct pixel) * BITS_IN_BYTE;
    header.biCompression = BI_COMPRESSION;
    header.biSizeImage = height * width * sizeof(struct pixel);
    header.biXPelsPerMeter = BI_X_PIXELS_PER_METER;
    header.biYPelsPerMeter = BI_Y_PIXELS_PER_METER;
    header.biClrUsed = BI_CLR_USED;
    header.biClrImportant = BI_CLR_IMPORTANT;

    return header;
}

/*  serializer   */
enum write_status to_bmp(FILE *out, struct image const *img) {
    struct bmp_header header = get_header(img->width, img->height);

    size_t count = fwrite(&header, sizeof(struct bmp_header), 1, out);

    if (count != 1) {
        return WRITE_INVALID_HEADER;
    }

    for (uint32_t row = 0; row < img->height; row++) {
        count = fwrite(img->data + row * img->width, sizeof(struct pixel), img->width, out);

        if (count != img->width) {
            return WRITE_INVALID_BITS;
        }

        //skip padding
        fseek(out, (long) get_paddings(img->width), SEEK_CUR);
    }

    return WRITE_OK;
}
