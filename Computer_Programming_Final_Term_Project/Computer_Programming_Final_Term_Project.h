#ifndef COMPUTER_PROGRAMMING_FINAL_TERM_PROJECT_H
#define COMPUTER_PROGRAMMING_FINAL_TERM_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define METHOD_STEP 14

void (*volatile const PROCESS[METHOD_STEP])(void);

void get_length     (void);
void get_code       (void);
void sort_code      (void);
void take_format    (void);
void calibrate_code (void);
void binary_code    (void);
void reverse_code   (void);
void get_data       (void);
void empty_buffer   (void);
void empty_status   (void);

void boundary_check (void);
void split_check    (void);
void C_check        (void);
void K_check        (void);

void print_code     (void);
void print_code_buf (void);
void print_data     (void);

#endif