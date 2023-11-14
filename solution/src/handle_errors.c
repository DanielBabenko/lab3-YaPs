//
// Created by danie on 14.11.2023.
//
#include <stdlib.h>

#include "../libraries/bmp_io.h"
#include "../libraries/exit_codes.h"

void handle_read_errors(enum read_status r_status) {
    printf("Read error: ");
    if (r_status == READ_INVALID_SIGNATURE) {
        printf("invalid signature.");
    } else if (r_status == READ_INVALID_BITS) {
        printf("invalid bits.");
    } else if (r_status == READ_INVALID_HEADER) {
        printf("invalid header.");
    }
}

void handle_write_errors(enum write_status w_status) {
    printf("Write error: ");
    if (w_status == WRITE_INVALID_HEADER) {
        printf("invalid header.");
    } else if (w_status == WRITE_INVALID_BITS) {
        printf("invalid bits.");
    }
}

void handle_out_of_memory_error(void) {
    printf("Out of memory!!!");
    exit(OUT_OF_MEMORY_EXIT_CODE);
}