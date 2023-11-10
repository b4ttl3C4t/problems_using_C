#ifndef COMPUTER_PROGRAMMING_FINAL_TERM_PROJECT_H
#define COMPUTER_PROGRAMMING_FINAL_TERM_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool scan_code       (void);
bool sort_code       (void);
bool take_format     (void);
bool calibrate_code  (void);
bool binary_code     (void);
bool reverse_code    (void);
bool get_data        (void);

bool split_check     (void);
bool C_check         (int32_t [], int32_t);
bool K_check         (int32_t [], int32_t);
bool boundary_check  (void);
bool decode_table    (int32_t);

#endif