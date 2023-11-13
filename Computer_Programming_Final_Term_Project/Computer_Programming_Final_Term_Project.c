/*
 * Computer_Programming_Final_Term_Project.c
 * 
 * 2023.11.10-2023.11.13, B11215024.
 * This file is for scanning barcode and decoding its numbers to string form.
 * 
 * The code format as following:
 *  [start character]{split}     |
 *  [data]                       |
 *  [stop character]             |
 * 
 * The data format as following:
 *  [encoded character_1]{split} |
 *  [encoded character_2]{split} |
 *               ...             |
 *  [encoded character_n]{split} |
 *  [checked character_C]{split} |
 *  [checked character_K]{split} |
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

//Programming status flag.
enum STATUS_FLAG
{
    STATUS_EMPTY_FLAG, 
    STATUS_EXIT_FLAG, 
    STATUS_BAD_FLAG, 
    STATUS_BAD_C_FLAG, 
    STATUS_BAD_K_FLAG, 
};

//For storing the barcode's information.
static uint32_t code        [CODE_SIZE] = {0};
static uint32_t code_buf    [CODE_SIZE] = {0};
static data_t   data        [DATA_SIZE] = {'\0'};

//For main process program.
static uint8_t  step, status;
static uint8_t  status_code = STATUS_EMPTY_FLAG;

//For interative variable.
static uint32_t each, i, j;
static uint32_t count, m, n;

//For constructing the format standard.
static double   narrow_format, wide_format;
static uint32_t narrow_bar,    wide_bar;

//An array of constant pointers to function (void) returning boolean data type.
//Executing the array step by step to get the information of barcode.
void (*volatile const PROCESS[METHOD_STEP])(void) = 
{
    get_length, 
    boundary_check, 
    get_code, 
    sort_code, 
    take_format, 
    calibrate_code, 
    binary_code, 
    reverse_code, 
    split_check, 
    get_data, 
    C_check, 
    K_check, 
    print_data
};

//Internal function.
static inline uint8_t   check_status    (void);
static inline double    bias_lower      (double);
static inline double    bias_upper      (double);
static inline uint64_t  char_to_weight  (char);
static inline char      weight_to_char  (uint64_t);
static inline void      code_to_data    (uint32_t, uint32_t *);
static inline uint32_t  data_decode     (uint32_t);
static inline uint32_t  data_length     (void);





int main(void)
{
    while(1)
    {
        status_code = STATUS_EMPTY_FLAG;

        for(step = 0; step < METHOD_STEP; ++step)
        {
            PROCESS[step]();
            status = check_status();
            
            if(status == 1)
            {
                return 0;
            }
            
            if(status == 2)
            {
                break;
            }
        }

        empty_buffer();
    }
}

void get_length(void)
{
    ++count;
    fscanf(stdin, "%u", &m);
    fgetc(stdin);

    n = data_length();

    if(m == 0)
    {
        status_code = STATUS_EXIT_FLAG;
    }
}

//Scaning numbers of the barcode and the code buffer from original code.
void get_code(void)
{
    for(each = 0; each < m; ++each)
    {
        fscanf(stdin, "%u", &code[each]);
        getc(stdin);

        code_buf[each] = code[each];
    }
}

//Sorting the code buffer to take the format easier.
void sort_code(void)
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
}

//Constructing the format of numbers
void take_format(void)
{
    static double summation;

    summation = narrow_format = wide_format = 0;

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

    for(each = each + 1; each < m - 1; ++each)
    {
        //Returning error when probing two more different value.
        if((code_buf[each + 1] - code_buf[each]) > (bias_upper(code[each]) - bias_lower(code[each])))
        {
            status_code = STATUS_BAD_FLAG;
            return;
        }
    }
    wide_bar = wide_format = narrow_bar * 2;
}

//Calibrating numbers of the code to conform to the format standard.
void calibrate_code(void)
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

        status_code = STATUS_BAD_FLAG;
        return;
    }
}

//Translating the numbers from decimal to binary.
void binary_code(void)
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
}

//Probing whether the barcode is reverse and its START/STOP are identical.
void reverse_code(void)
{
    //Invalid code format when there are difference between START and STOP.
    if(code[0] != code[m - 5] ||
       code[1] != code[m - 4] ||
       code[2] != code[m - 3] ||
       code[3] != code[m - 2] ||
       code[4] != code[m - 1])
    {
        status_code = STATUS_BAD_FLAG;
        return;
    }

    //Not reversing the code if the START/STOP aren't reverse as well.
    //(Note the START/STOP are 00110).
    if(!code[0] &&
       !code[1] &&
        code[2] &&
        code[3] &&
       !code[4])
    {
        return;
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

        return;
    }

    //Invalid code format when the START/STOP are unmatched by 00110 or 01100.
    status_code = STATUS_BAD_FLAG;
}

//Translating information from binary code to data format.
void get_data(void)
{
    //Getting the data from binary code.
    for(i = 1 + DATA_WIDTH, j = 0;
        i < m - DATA_WIDTH;
        i += DATA_WIDTH + 1, ++j)
    {
        code_to_data(j, code + i);
    }

    //Decoding the data to character based on its value.
    for(each = 0; each < n; ++each)
    {
        if(!data_decode(each))
        {
            status_code = STATUS_BAD_FLAG;
            return;
        }
    }

    /*The check code C and K one are not the original data,
     *they're just check code, 
     *so you can expel them to get original length now.
     */
    n -= 2;
}

//Setting the buffer to zero.
void empty_buffer(void)
{
    for(each = 0; each < m; ++each)
    {
        code[each] = code_buf[each] = 0;
    }

    //Note that the check code C and K are in *data*.
    for(each = 0; each < n + 2; ++each)
    {
        data[each].character = '\0';
    }

    status_code = STATUS_EMPTY_FLAG;
}





//Checking the correctness code and data.
//Checking whether the barcode's boundary match the data format.
void boundary_check(void)
{
    if( m % (DATA_WIDTH + 1) != DATA_WIDTH ||
        m < LOWER_WIDTH ||
        m > UPPER_WIDTH)
    {
        //Absorbing the input data because of the invalid *m*.
        get_code();
        empty_buffer();

        status_code = STATUS_BAD_FLAG;
    }
}

void split_check(void)
{
    //Probing whether each split bar is light narrow bar.
    for(each = 0; each <= n; ++each)
    {
        if(code[DATA_WIDTH + each * (DATA_WIDTH + 1)] != 0)
        {
            status_code = STATUS_BAD_FLAG;
            return;
        }
    }
}

void C_check(void)
{
    static uint64_t summation;
    
    summation = 0;
    for(i = 1; i <= n; ++i)
    {
        summation += ((n - i) % 10 + 1) * char_to_weight(data[i - 1].character);
    }
    summation %= 11;

    if(data[n].character != weight_to_char(summation))
    {
        status_code = STATUS_BAD_C_FLAG;
    }
}

void K_check(void)
{
    static uint64_t summation;

    summation = 0;
    for(i = 1; i <= n + 1; ++i)
    {
        summation += ((n - i + 1) % 9 + 1) * char_to_weight(data[i - 1].character);
    }
    summation %= 11;

    if(data[n + 1].character != weight_to_char(summation))
    {
        status_code = STATUS_BAD_K_FLAG;
    }
}





//The print function for test.
void print_code_buf(void)
{
    printf("Case %d: ", count);

    for(each = 0; each < m; ++each)
    {
        printf("%3d", code_buf[each]);
    }

    printf("%c", '\n');
}

void print_code(void)
{
    printf("Case %d: ", count);

    for(each = 0; each < m; ++each)
    {
        printf("%3d", code[each]);
    }

    printf("%c", '\n');
}

void print_data(void)
{
    printf("Case %d: ", count);

    for(each = 0; each < n; ++each)
    {
        printf("%c", data[each].character);
    }
    
    printf("%c", '\n');
}





//The implementation of the internal functions.
static inline uint8_t check_status(void)
{
    //printf("|%d %d \n", step, status_code);

    switch(status_code)
    {
    case STATUS_EMPTY_FLAG:
        return 0;

    case STATUS_EXIT_FLAG:
        return 1;

    case STATUS_BAD_FLAG:
        printf("Case %d: bad code\n", count);
        return 2;

    case STATUS_BAD_C_FLAG:
        printf("Case %d: bad C\n", count);
        return 2;

    case STATUS_BAD_K_FLAG:
        printf("Case %d: bad K\n", count);
        return 2;

    default:
        return 0;
    }
}

static inline uint64_t char_to_weight(char ch)
{
    if(ch == '-')
        return 10;
    
    return ch ^ 48;
}

static inline char weight_to_char(uint64_t i)
{
    if(i == 10)
        return '-';
    
    return i ^ 48;
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

static inline void code_to_data(uint32_t index, uint32_t *code_index)
{
    //Storing each corresponding numbers to data.
    data[index].b1 = code_index[4];
    data[index].b2 = code_index[3];
    data[index].b3 = code_index[2];
    data[index].b4 = code_index[1];
    data[index].b5 = code_index[0];
}

static inline uint32_t data_length(void)
{
    return (m - DATA_WIDTH * 2 - 1) / 6;
}

static inline uint32_t data_decode(uint32_t index)
{
    switch(data[index].character)
    {
    case  1:    //weight: 00001 | weight summation: 01
        data[index].character = '0';
        break;
    case 17:    //weight: 10001 | weight summation: 17
        data[index].character = '1';
        break;
    case  9:    //weight: 01001 | weight summation: 09
        data[index].character = '2';
        break;
    case 24:    //weight: 11000 | weight summation: 24
        data[index].character = '3';
        break;
    case  5:    //weight: 00101 | weight summation: 05
        data[index].character = '4';
        break;
    case 20:    //weight: 10100 | weight summation: 20
        data[index].character = '5';
        break;
    case 12:    //weight: 01100 | weight summation: 12
        data[index].character = '6';
        break;
    case  3:    //weight: 00011 | weight summation: 03
        data[index].character = '7';
        break;
    case 18:    //weight: 10010 | weight summation: 18
        data[index].character = '8';
        break;
    case 16:    //weight: 10000 | weight summation: 16
        data[index].character = '9';
        break;
    case  4:    //weight: 00100 | weight summation: 04
        data[index].character = '-';
        break;
    case  6:    //weight: 00110 | weight summation: 06
        data[index].character = 'S';
        break;
    default:    //Returning false when the weight is invalid.
        return 0;
    };

    return 1;
}