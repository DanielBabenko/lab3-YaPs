#include <stdio.h>
#include <stdlib.h>

#include "../libraries/bmp_io.h"
#include "../libraries/exit_codes.h"
#include "../libraries/handle_errors.h"
#include "../libraries/transform.h"

#define ARGUMENTS_NUMBER 4
#define SOURCE_IMAGE_ARGUMENT_NUMBER 1
#define DESTINATION_IMAGE_ARGUMENT_NUMBER 2
#define ANGLE_ARGUMENT_NUMBER 3

int main(int argc, char **argv) {
    if (argc != ARGUMENTS_NUMBER) {
        printf("Wrong arguments!\n");
        printf("My program receives three arguments: <source-image> <transformed-image> <angle>.");
        return WRONG_ARGUMENTS_EXIT_CODE;
    }

    const char *source_image = argv[SOURCE_IMAGE_ARGUMENT_NUMBER];
    const char *transformed_image = argv[DESTINATION_IMAGE_ARGUMENT_NUMBER];
    const char *angle = argv[ANGLE_ARGUMENT_NUMBER];

    FILE *in_p = fopen(source_image, "rb");
    FILE *out_p = fopen(transformed_image, "wb");       // if this file doesn't exist, it's created

    if (in_p == NULL) {
        printf("Source file doesnt exist");
        return FILE_DOESNT_EXISTS_EXIT_CODE;
    }

    struct image source;
    enum read_status r_status = from_bmp(in_p, &source);

    if (r_status != READ_OK) {
        handle_read_errors(r_status);
        return READ_ERROR_EXIT_CODE;
    }

    struct image destination;
    uint32_t int_angle = atoi(angle);

    if (int_angle == 0) {
        destination = source;
    } else if (int_angle == 90 || int_angle == -270) {
        destination = rotate90(source);
    } else if (int_angle == 180 || int_angle == -180) {
        destination = rotate180(source);
    } else if (int_angle == 270 || int_angle == -90) {
        destination = rotate270(source);
    } else {
        printf("Wrong angle!!\n");
        printf("Allowable angle values are 0, +-90, +-180, +-270.");
        return WRONG_ARGUMENTS_EXIT_CODE;
    }

    enum write_status w_status = to_bmp(out_p, &destination);

    if (source.data != destination.data) {
        free(destination.data);
    }
    free(source.data);

    if (w_status != WRITE_OK) {
        handle_write_errors(w_status);
        return WRITE_ERROR_EXIT_CODE;
    }

    fclose(out_p);
    fclose(in_p);

    printf("Everything is GOOD!");
    return 0;
}