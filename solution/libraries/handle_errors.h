#ifndef IMAGE_TRANSFORMER_HANDLE_ERRORS_H
#define IMAGE_TRANSFORMER_HANDLE_ERRORS_H

#include "bmp_io.h"

void handle_read_errors(enum read_status r_status);

void handle_write_errors(enum write_status w_status);

void handle_out_of_memory_error(void);

#endif //IMAGE_TRANSFORMER_HANDLE_ERRORS_H