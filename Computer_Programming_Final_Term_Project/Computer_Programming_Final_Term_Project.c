/*
 * Computer_Programming_Final_Term_Project.c
 * 
 * 2023.11.10-2023.11.12, B11215024.
 * This file is for scanning barcode and decoding its numbers to string form.
 * 
 * The code format as following:
 *  [start character]{split}     |
 *  [data]                       |
 *  [check character_C]{split}   |
 *  [check character_K]{split}   |
 *  [end character]              |
 * 
 * The data format as following:
 *  [encoded character_1]{split} | 
 *  [encoded character_2]{split} | 
 *               ...             | 
 *  [encoded character_n]{split} |
 * 
 * Note that every encoded character is shown with 5 bits
 */

#include "Computer_Programming_Final_Term_Project.h"

#define CODE_SIZE   150
#define TABLE_SIZE  12
#define DATA_SIZE   32
#define DATA_WIDTH  5
#define UPPER_WIDTH 150
#define LOWER_WIDTH 29
#define BIAS_RANGE  0.05

#define SWAP(x, y)  (x) = (x) ^ (y);    \
                    (y) = (x) ^ (y);    \
                    (x) = (x) ^ (y);

//Data format (5 bits).
typedef union data_s
{
    struct
    {
        uint8_t b1: 1;
        uint8_t b2: 1;
        uint8_t b3: 1;
        uint8_t b4: 1;
        uint8_t b5: 1;
    };
    char    character;
} data_t;

//For storing the barcode's information.
static uint32_t code        [CODE_SIZE] = {0};
static uint32_t code_buf    [CODE_SIZE] = {0};
static data_t   data        [DATA_SIZE] = {'\0'};

//For interative variable.
static uint32_t each, i, j;
static uint32_t count, m, length;

//For constructing the format standard.
static double   narrow_format, wide_format;
static uint32_t narrow_bar,    wide_bar;

//An array of constant pointers to function (void) returning boolean data type.
//Executing the array step by step to get the information of barcode.
bool (*volatile const PROCESS[METHOD_STEP])(void) = 
{
    boundary_check, 
    scan_code, 
    sort_code, 
    take_format, 
    calibrate_code, 
    binary_code, 
    reverse_code, 
    split_check
    //get_data, 
    //empty_buffer, 
};

//Internal function.
static inline int8_t    char_to_int     (int8_t);
static inline double    bias_lower      (double);
static inline double    bias_upper      (double);
static inline void      data_weight     (uint32_t, uint32_t *);
static inline uint32_t  data_length     (void);
static inline bool      decode_table    (uint32_t);

int main(void)
{
    //FILE *file_stream = fopen("test.txt", "r");
    uint8_t step;

    while(1)
    {
        ++count;
        fscanf(stdin, "%d", &m);
        fgetc(stdin);
        
        length = data_length();
        printf("%d|\n", length);
        if(m == 0)
        {
            break;
        }

        for(step = 0; step < METHOD_STEP; ++step)
        {
            if(!PROCESS[step]())
            {
                printf("#Case%d : bad code\n", count);
                break;
            }
        }

        for(each = 0; each < m; ++each)
        {
            printf("%2d ", code[each]);
        }
    }
    
    //fclose(file_stream);

    return 0;
}

//Checking whether the barcode's boundary match the data format.
bool boundary_check(void)
{
    if(m % (DATA_WIDTH + 1) != DATA_WIDTH)
    {
        return false;
    }

    if(m < LOWER_WIDTH)
    {
        return false;
    }

    if(m > UPPER_WIDTH)
    {
        return false;
    }
    
    return true;
}

//Scaning numbers of the barcode and the code buffer from original code.
bool scan_code(void)
{
    for(each = 0; each < m; ++each)
    {
        fscanf(stdin, "%d", &code[each]);
        getc(stdin);

        code_buf[each] = code[each];
    }

    return true;
}

//Sorting the code buffer to take the format easier.
bool sort_code(void)
{
    for(i = 0; i < m - 1; ++i)
    {
        for(j = 0; j < m - 1; ++j)
        {
            if(code_buf[j] > code_buf[j + 1])
            {
                SWAP(code_buf[j], code_buf[j + 1]);
            }
        }
    }

    return true;
}

//Constructing the format of numbers
bool take_format(void)
{
    static double summation, break_point;
    summation = 0.0;
    narrow_format = wide_format = 0;

    for(each = 0; each < m - 1; ++each)
    {
        summation += code_buf[each];
        if((code_buf[each + 1] - code_buf[each]) > (bias_upper(code[each]) - bias_lower(code[each])))
        {
            narrow_format = summation / (each + 1);
            narrow_bar = narrow_format + 0.5;
            break;
        }
    }

    summation = 0.0;
    ++each;
    break_point = each;
    for(; each < m - 1; ++each)
    {
        summation += code_buf[each];

        //Returning error when probing two more different value.
        if((code_buf[each + 1] - code_buf[each]) > (bias_upper(code[each]) - bias_lower(code[each])))
        {
            return false;
        }
    }
    wide_format = summation / (each - break_point);
    wide_bar = wide_format + 0.5;

    return true;
}

//Calibrating numbers of the code to conform to the format standard.
bool calibrate_code(void)
{
    for(each = 0; each < m; ++each)
    {
        if( bias_lower(narrow_format) < code[each] && 
            bias_upper(narrow_format) > code[each])
        {
            code[each] = narrow_bar;
            continue;
        }
        
        if( bias_lower(wide_format) < code[each] &&
            bias_upper(wide_format) > code[each])
        {
            code[each] = wide_bar;
            continue;
        }

        return false;
    }

    return true;
}

//Translating the numbers from decimal to binary.
bool binary_code(void)
{
    for(each = 0; each < m; ++each)
    {
        if(code[each] == narrow_bar)
        {
            code[each] = 0;
        }

        if(code[each] == wide_bar)
        {
            code[each] = 1;
        }
    }

    return true;
}

//Probing whether the barcode is reverse and its START/STOP are identical.
bool reverse_code(void)
{
    //Invalid code format when there are difference between START and STOP.
    if(code[0] != code[m - 5] ||
       code[1] != code[m - 4] ||
       code[2] != code[m - 3] ||
       code[3] != code[m - 2] ||
       code[4] != code[m - 1])
    {
        return false;
    }

    //Not reversing the code if the START/STOP aren't reverse as well.
    //(Note the START/STOP are 00110).
    if(!code[0] &&
       !code[1] &&
        code[2] &&
        code[3] &&
       !code[4])
    {
        return true;
    }

    //Reversing the code if the START/STOP are reverse as well.
    //(Note the START/STOP are 01100).
    if(!code[0] &&
        code[1] &&
        code[2] &&
       !code[3] &&
       !code[4])
    {
        for(i = 0, j = m-1; i < j; ++i, --j)
        {
            SWAP(code[i], code[j]);
        }

        return true;
    }

    //Invalid code format when the START/STOP are unmatched by 00110 or 01100.
    return false;
}

bool split_check(void)
{
    //Probing whether each split bar is light narrow bar.
    //* + 2 * means that you have to consider the check code C K.
    for(each = 0; each < length + 2; ++each)
    {
        if(code[each * DATA_WIDTH] != 0)
        {
            return false;
        }
    }

    return true;
}

bool get_data(void)
{
    for(each = 0 + DATA_WIDTH;
        each < m - DATA_WIDTH;
        each += DATA_WIDTH)
    {
        data_weight(each, code + each);
    }

    for(each = 0; each < length; ++each)
    {
        if(decode_table(each))
        {
            return false;
        }
    }

    return true;
}

static inline int8_t char_to_int(int8_t ch)
{
    return ch ^ 48;
}

//Getting the lower limit of x.
double bias_lower(double x)
{
    return (x - x * BIAS_RANGE);
}

//Getting the upper limit of x.
double bias_upper(double x)
{
    return (x + x * BIAS_RANGE);
}

static inline void data_weight(uint32_t index, uint32_t *code_index)
{
    //Storing each corresponding numbers to data.
    data[index].b1 = code_index[0];
    data[index].b2 = code_index[1];
    data[index].b3 = code_index[2];
    data[index].b4 = code_index[3];
    data[index].b5 = code_index[4];
}

static inline uint32_t data_length(void)
{
    return (m - DATA_WIDTH * 4 - 3) / 5;
}

static inline bool decode_table(uint32_t index)
{
    switch(data[index].character)
    {
    case  1:     //weight: 00001 | weight summation: 01
        data[index].character = '0';
        break;
    case 17:     //weight: 10001 | weight summation: 17
        data[index].character = '1';
        break;
    case  9:     //weight: 01001 | weight summation: 09
        data[index].character = '2';
        break;
    case 24:     //weight: 11000 | weight summation: 24
        data[index].character = '3';
        break;
    case  5:     //weight: 00101 | weight summation: 05
        data[index].character = '4';
        break;
    case 20:     //weight: 10100 | weight summation: 20
        data[index].character = '5';
        break;
    case 12:     //weight: 01100 | weight summation: 12
        data[index].character = '6';
        break;
    case  3:     //weight: 00011 | weight summation: 03
        data[index].character = '7';
        break;
    case 18:     //weight: 10010 | weight summation: 18
        data[index].character = '8';
        break;
    case 16:     //weight: 10000 | weight summation: 16
        data[index].character = '9';
        break;
    case  4:     //weight: 00100 | weight summation: 04
        data[index].character = '-';
        break;
    case  6:     //weight: 00110 | weight summation: 06
        data[index].character = 'S';
        break;
    default:    //Returning false when the weight is invalid.
        return false;
    };

    return true;
}