#ifndef COMPUTER_PROGRAMMING_FINAL_TERM_PROJECT_H
#define COMPUTER_PROGRAMMING_FINAL_TERM_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define METHOD_STEP 13

//You have to initializate the barcode type like *barcode_t barcode = {0};* .
typedef struct barcode_s barcode_t;

void (*volatile const PROCESS[METHOD_STEP])(barcode_t *);

void get_length     (barcode_t *);
void get_code       (barcode_t *);
void sort_code      (barcode_t *);
void take_format    (barcode_t *);
void calibrate_code (barcode_t *);
void binary_code    (barcode_t *);
void reverse_code   (barcode_t *);
void get_data       (barcode_t *);
void empty_buffer   (barcode_t *);

void boundary_check (barcode_t *);
void split_check    (barcode_t *);
void C_check        (barcode_t *);
void K_check        (barcode_t *);

void print_code     (barcode_t *);
void print_code_buf (barcode_t *);
void print_data     (barcode_t *);

#endif