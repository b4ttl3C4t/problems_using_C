/*
 * Computer_Programming_Final_Term_Project.c
 * 
 * 2023.11.10-2023.11.30, B11215024.
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

#define FILE_STREAM_INPUT 1
//#define FILE_STREAM_OUTPUT 1

#define CODE_SIZE   150
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

typedef struct barcode_s
{
    //For storing the barcode's information.
    uint32_t code[CODE_SIZE];
    uint32_t buff[CODE_SIZE];
    data_t   data[DATA_SIZE];

    //For main process program.
    uint8_t status;

    //For interative variable.
    uint32_t count, m, n;

    //For constructing the format standard.
    uint32_t narrow_bar, wide_bar;
} barcode_t;



//An array of read-only volatile pointers to function (void) returning nothing.
//Executing the array step by step to get the information of barcode.
void (*volatile const PROCESS[METHOD_STEP])(barcode_t *) = 
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
static inline uint8_t   check_status    (barcode_t *);
static inline double    bias_lower      (double);
static inline double    bias_upper      (double);
static inline uint64_t  char_to_weight  (char);
static inline char      weight_to_char  (uint64_t);
static inline void      code_to_data    (barcode_t *, uint32_t, uint32_t *);
static inline uint32_t  data_decode     (barcode_t *, uint32_t);
static inline uint32_t  data_length     (barcode_t *);



#ifdef FILE_STREAM_INPUT
FILE *fp_input;
#endif

#ifdef FILE_STREAM_OUTPUT
FILE *fp_output;
#endif

int main(void)
{
    uint8_t status_code, step;
    barcode_t barcode = {0};

	#ifdef FILE_STREAM_INPUT
    fp_input = fopen("test.txt", "r");
	#endif

    #ifdef FILE_STREAM_OUTPUT
    fp_output = fopen("result.txt", "w");
	#endif
	
    while(1)
    {
        barcode.status = STATUS_EMPTY_FLAG;

        for(step = 0; step < METHOD_STEP; ++step)
        {
            PROCESS[step](&barcode);
            //printf("|%u|\n", step);
            status_code = check_status(&barcode);
            
            if(status_code == 1)
            {
                return 0;
            }
            
            if(status_code == 2)
            {
                break;
            }
        }
        empty_buffer(&barcode);
    }

	#ifdef FILE_STREAM_INPUT
    fclose(fp_input);
    #endif

    #ifdef FILE_STREAM_OUTPUT
    fclose(fp_output);
    #endif
}

void get_length(barcode_t *barcode)
{
    ++barcode->count;

#ifdef FILE_STREAM_INPUT
    fscanf(fp_input, "%u", &barcode->m);
    fgetc(fp_input);
#else
    fscanf(stdin, "%u", &barcode->m);
    fgetc(stdin);
#endif

    barcode->n = data_length(barcode);

    if(barcode->m == 0)
    {
        barcode->status = STATUS_EXIT_FLAG;
    }
}

//Scaning numbers of the barcode and the code buffer from original code.
void get_code(barcode_t *barcode)
{
    register uint32_t each;

    for(each = 0; each < barcode->m; ++each)
    {
#ifdef FILE_STREAM_INPUT
        fscanf(fp_input, "%u", &barcode->code[each]);
        fgetc(fp_input);
#else
        fscanf(stdin, "%u", &barcode->code[each]);
        fgetc(stdin);
#endif

        barcode->buff[each] = barcode->code[each];
        
        if(barcode->code[each] == 0)
        {
            barcode->status = STATUS_BAD_FLAG;
        }
    }
}

//Sorting the barcode->code buffer to take the format easier.
void sort_code(barcode_t *barcode)
{
    register uint32_t i, j;

    for(i = 0; i < barcode->m - 1; ++i)
    {
        for(j = 0; j < barcode->m - 1; ++j)
        {
            if(barcode->buff[j] > barcode->buff[j + 1])
            {
                SWAP(barcode->buff[j], barcode->buff[j + 1]);
            }
        }
    }
}

//Constructing the format of numbers
void take_format(barcode_t *barcode)
{
    register uint32_t each;

    for(each = 0; each < barcode->m - 1; ++each)
    {
        if((barcode->buff[each + 1] - barcode->buff[each]) > (bias_upper(barcode->code[each + 1]) - bias_lower(barcode->code[each + 1])))
        {
            break;
        }
    }
    
    double min = ((barcode->buff[0]    * 2  < barcode->buff[each + 1])?          barcode->buff[0]    * 2:  barcode->buff[each + 1]);
    double max = ( barcode->buff[each] * 2  > barcode->buff[barcode->m - 1]   )? barcode->buff[each] * 2:  barcode->buff[barcode->m - 1];

    barcode->wide_bar    = (min + max) / 2 + 0.5;
    barcode->narrow_bar  = (min + max) / 4 + 0.25;
}

//Calibrating numbers of the code to conform to the format standard.
void calibrate_code(barcode_t *barcode)
{
    register uint32_t each;

    for(each = 0; each < barcode->m; ++each)
    {
        if( bias_lower(barcode->narrow_bar) <= barcode->code[each] && 
            bias_upper(barcode->narrow_bar) >= barcode->code[each])
        {
            barcode->code[each] = barcode->narrow_bar;
            continue;
        }
        
        if( bias_lower(barcode->wide_bar) <= barcode->code[each] &&
            bias_upper(barcode->wide_bar) >= barcode->code[each])
        {
            barcode->code[each] = barcode->wide_bar;
            continue;
        }
        /*printf("|%lf %lf %u %lf %lf %u %lf %lf %u|\n", 
                    bias_lower(narrow_bar), bias_upper(narrow_bar), narrow_bar,
                    bias_lower(wide_bar), bias_upper(wide_bar), wide_bar, 
                    min, max, barcode->code[each]);*/

        barcode->status = STATUS_BAD_FLAG;
        return;
    }
}

//Translating the numbers from decimal to binary.
void binary_code(barcode_t *barcode)
{
    register uint32_t each;

    for(each = 0; each < barcode->m; ++each)
    {
        if(barcode->code[each] == barcode->narrow_bar)
        {
            barcode->code[each] = 0;
        }

        if(barcode->code[each] == barcode->wide_bar)
        {
            barcode->code[each] = 1;
        }
    }
}

//Probing whether the barcode is reverse and its START/STOP are identical.
void reverse_code(barcode_t *barcode)
{
    register uint32_t i, j;

    //Invalid barcode->code format when there are difference between START and STOP.
    if(barcode->code[0] != barcode->code[barcode->m - 5] ||
       barcode->code[1] != barcode->code[barcode->m - 4] ||
       barcode->code[2] != barcode->code[barcode->m - 3] ||
       barcode->code[3] != barcode->code[barcode->m - 2] ||
       barcode->code[4] != barcode->code[barcode->m - 1])
    {
        barcode->status = STATUS_BAD_FLAG;
        return;
    }

    //Not reversing the barcode->code if the START/STOP aren't reverse as well.
    //(Note the START/STOP are 00110).
    if(!barcode->code[0] &&
       !barcode->code[1] &&
        barcode->code[2] &&
        barcode->code[3] &&
       !barcode->code[4])
    {
        return;
    }

    //Reversing the barcode->code if the START/STOP are reverse as well.
    //(Note the START/STOP are 01100).
    if(!barcode->code[0] &&
        barcode->code[1] &&
        barcode->code[2] &&
       !barcode->code[3] &&
       !barcode->code[4])
    {
        for(i = 0, j = barcode->m-1; i < j; ++i, --j)
        {
            SWAP(barcode->code[i], barcode->code[j]);
        }

        return;
    }

    //Invalid barcode->code format when the START/STOP are unmatched by 00110 or 01100.
    barcode->status = STATUS_BAD_FLAG;
}

//Translating information from binary barcode->code to barcode->data format.
void get_data(barcode_t *barcode)
{
    register uint32_t each, i, j;

    //Getting the barcode->data from binary barcode->code.
    for(i = 1 + DATA_WIDTH, j = 0;
        i < barcode->m - DATA_WIDTH;
        i += DATA_WIDTH + 1, ++j)
    {
        code_to_data(barcode, j, barcode->code + i);
    }

    //Decoding the barcode->data to character based on its value.
    for(each = 0; each < barcode->n; ++each)
    {
        if(!data_decode(barcode, each))
        {
            barcode->status = STATUS_BAD_FLAG;
            return;
        }
    }

    /*The check barcode->code C and K one are not the original barcode->data,
     *they're just check barcode->code, 
     *so you can expel them to get original length.
     */
    barcode->n -= 2;
}

//Setting the buffer to zero.
void empty_buffer(barcode_t *barcode)
{
    register uint32_t each;

    for(each = 0; each < barcode->m; ++each)
    {
        barcode->code[each] = barcode->buff[each] = 0;
    }

    //Note that the check barcode->code C and K are in *barcode->data*.
    for(each = 0; each < barcode->n + 2; ++each)
    {
        barcode->data[each].character = '\0';
    }

    barcode->status = STATUS_EMPTY_FLAG;
}





//Checking the correctness barcode->code and barcode->data.
//Checking whether the barcode's boundary match the barcode->data format.
void boundary_check(barcode_t *barcode)
{
    if( barcode->m % (DATA_WIDTH + 1) != DATA_WIDTH ||
        barcode->m < LOWER_WIDTH ||
        barcode->m > UPPER_WIDTH)
    {
        //Absorbing the input barcode->data because of the invalid *barcode->m*.
        get_code(barcode);
        empty_buffer(barcode);

        barcode->status = STATUS_BAD_FLAG;
    }
}

void split_check(barcode_t *barcode)
{
    register uint32_t each;

    //Probing whether each split bar is light narrow bar.
    for(each = 0; each <= barcode->n; ++each)
    {
        if(barcode->code[DATA_WIDTH + each * (DATA_WIDTH + 1)] != 0)
        {
            barcode->status = STATUS_BAD_FLAG;
            return;
        }
    }
}

void C_check(barcode_t *barcode)
{
    register uint32_t summation, i;

    summation = 0;
    for(i = 1; i <= barcode->n; ++i)
    {
        summation += ((barcode->n - i) % 10 + 1) * char_to_weight(barcode->data[i - 1].character);
    }
    summation %= 11;

    //*barcode->n* means the position of the check barcode->code C.
    if(barcode->data[barcode->n].character != weight_to_char(summation))
    {
        barcode->status = STATUS_BAD_C_FLAG;
    }
}

void K_check(barcode_t *barcode)
{
    register uint32_t summation, i;

    summation = 0;
    for(i = 1; i <= barcode->n + 1; ++i)
    {
        summation += ((barcode->n - i + 1) % 9 + 1) * char_to_weight(barcode->data[i - 1].character);
    }
    summation %= 11;

    //*barcode->n + 1* means the position of the check barcode->code K.
    if(barcode->data[barcode->n + 1].character != weight_to_char(summation))
    {
        barcode->status = STATUS_BAD_K_FLAG;
    }
}





//The print function for test.
void print_code_buf(barcode_t *barcode)
{
    register uint32_t each;

#ifdef FILE_STREAM_OUTPUT
    fprintf(fp_output, "Case %d: ", barcode->count);

    for(each = 0; each < barcode->m; ++each)
    {
        fprintf(fp_output, "%3d", barcode->buff[each]);
    }

    fprintf(fp_output, "%c", '\n');

#else
    fprintf(stdout, "Case %d: ", barcode->count);

    for(each = 0; each < barcode->m; ++each)
    {
        fprintf(stdout, "%3d", barcode->buff[each]);
    }

    fprintf(stdout, "%c", '\n');

#endif
}

void print_code(barcode_t *barcode)
{
    register uint32_t each;

#ifdef FILE_STREAM_OUTPUT
    fprintf(fp_output, "Case %d: ", barcode->count);

    for(each = 0; each < barcode->m; ++each)
    {
        fprintf(fp_output, "%3d", barcode->code[each]);
    }

    fprintf(fp_output, "%c", '\n');

    return;

#else
    fprintf(stdout, "Case %d: ", barcode->count);

    for(each = 0; each < barcode->m; ++each)
    {
        fprintf(stdout, "%3d", barcode->code[each]);
    }

    fprintf(stdout, "%c", '\n');
    
#endif
}

void print_data(barcode_t *barcode)
{
    register uint32_t each;

#ifdef FILE_STREAM_OUTPUT
    fprintf(fp_output, "Case %d: ", barcode->count);

    for(each = 0; each < barcode->n; ++each)
    {
        fprintf(fp_output, "%c", barcode->data[each].character);
    }
    
    fprintf(fp_output, "%c", '\n');

    return;
    
#else
    fprintf(stdout, "Case %d: ", barcode->count);

    for(each = 0; each < barcode->n; ++each)
    {
        fprintf(stdout, "%c", barcode->data[each].character);
    }
    
    fprintf(stdout, "%c", '\n');
    
#endif
}





//The implementation of the internal functions.
static inline uint8_t check_status(barcode_t *barcode)
{
    //fprintf(stdout, "|%d %d \n", step, barcode->status);

    switch(barcode->status)
    {
    case STATUS_EMPTY_FLAG:
        return 0;

    case STATUS_EXIT_FLAG:
        return 1;

    case STATUS_BAD_FLAG:
        #ifdef FILE_STREAM_OUTPUT
        fprintf(fp_output, "Case %d: bad code\n", barcode->count);
		#else
		fprintf(stdout, "Case %d: bad code\n", barcode->count);
        #endif
		return 2;

    case STATUS_BAD_C_FLAG:
        #ifdef FILE_STREAM_OUTPUT
        fprintf(fp_output, "Case %d: bad C\n", barcode->count);
		#else
		fprintf(stdout, "Case %d: bad C\n", barcode->count);
        #endif
		return 2;

    case STATUS_BAD_K_FLAG:
        #ifdef FILE_STREAM_OUTPUT
        fprintf(fp_output, "Case %d: bad K\n", barcode->count);
        #else
		fprintf(stdout, "Case %d: bad K\n", barcode->count);
        #endif
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

static inline void code_to_data(barcode_t *barcode, uint32_t index, uint32_t *code_index)
{
    //Storing each corresponding numbers to barcode->data.
    barcode->data[index].b1 = code_index[4];
    barcode->data[index].b2 = code_index[3];
    barcode->data[index].b3 = code_index[2];
    barcode->data[index].b4 = code_index[1];
    barcode->data[index].b5 = code_index[0];
}

static inline uint32_t data_length(barcode_t *barcode)
{
    return (barcode->m - DATA_WIDTH * 2 - 1) / 6;
}

static inline uint32_t data_decode(barcode_t *barcode, uint32_t index)
{
    switch(barcode->data[index].character)
    {
    case  1:    //weight: 00001 | weight summation: 01
        barcode->data[index].character = '0';
        break;
    case 17:    //weight: 10001 | weight summation: 17
        barcode->data[index].character = '1';
        break;
    case  9:    //weight: 01001 | weight summation: 09
        barcode->data[index].character = '2';
        break;
    case 24:    //weight: 11000 | weight summation: 24
        barcode->data[index].character = '3';
        break;
    case  5:    //weight: 00101 | weight summation: 05
        barcode->data[index].character = '4';
        break;
    case 20:    //weight: 10100 | weight summation: 20
        barcode->data[index].character = '5';
        break;
    case 12:    //weight: 01100 | weight summation: 12
        barcode->data[index].character = '6';
        break;
    case  3:    //weight: 00011 | weight summation: 03
        barcode->data[index].character = '7';
        break;
    case 18:    //weight: 10010 | weight summation: 18
        barcode->data[index].character = '8';
        break;
    case 16:    //weight: 10000 | weight summation: 16
        barcode->data[index].character = '9';
        break;
    case  4:    //weight: 00100 | weight summation: 04
        barcode->data[index].character = '-';
        break;
    case  6:    //weight: 00110 | weight summation: 06
        barcode->data[index].character = 'S';
        break;
    default:    //Returning false when the weight is invalid.
        return 0;
    };

    return 1;
}
