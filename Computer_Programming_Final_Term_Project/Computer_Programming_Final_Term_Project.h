#ifndef COMPUTER_PROGRAMMING_FINAL_TERM_PROJECT_H
#define COMPUTER_PROGRAMMING_FINAL_TERM_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define METHOD_STEP 13

bool (*volatile const PROCESS[METHOD_STEP])(void);

bool scan_code       (void);
bool sort_code       (void);
bool take_format     (void);
bool calibrate_code  (void);
bool binary_code     (void);
bool reverse_code    (void);
bool get_data        (void);
bool empty_buffer    (void);

bool boundary_check  (void);
bool split_check     (void);
bool C_check         (void);
bool K_check         (void);

bool print_code      (void);
bool print_code_buf  (void);
bool print_data      (void);

#endif