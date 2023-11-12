#include "Computer_Programming_Final_Term_Project.h"

#define CODE_SIZE   150
#define DATA_WIDTH  6
#define LOWER_WIDTH 29
#define METHOD_STEP 7
#define SWAP(x, y)  (x) = (x) ^ (y);    \
                    (y) = (x) ^ (y);    \
                    (x) = (x) ^ (y);

typedef union data_s
{
    uint8_t weight   : 5;
    char    character;
} data_t;

static int32_t  code        [CODE_SIZE] = {0};
static int32_t  code_buf    [CODE_SIZE] = {0};
static data_t   data        [CODE_SIZE] = {'\0'};

static int32_t  each, i, j;
static int32_t  count, m;

static double   narrow_format, wide_format;
static int32_t  narrow_bar,    wide_bar;

static inline void      code_weight     (data_t *);
static inline void      decode_table    (data_t *);
static inline double    bias_lower      (double);
static inline double    bias_upper      (double);

bool (*process[METHOD_STEP])(void) = 
{
    boundary_check, 
    scan_code, 
    sort_code, 
    take_format, 
    calibrate_code, 
    binary_code, 
    reverse_code, 
    //get_data
};

int main(void)
{
    //FILE *file_stream = fopen("test.txt", "r");
    uint8_t step;

    while(1)
    {
        ++count;
        fscanf(stdin, "%d", &m);
        fgetc(stdin);
        
        if(m == 0)
        {
            break;
        }

        for(step = 0; step <= 6; ++step)
        {
            if(!process[step]())
            {
                printf("#Case%d : bad code\n", count);
                break;
            }
        }

        for(each = 0; each < m; ++each)
        {
            printf("%2d ", code[each]);
        }
        //printf("|%lf %lf|\n", narrow_format, wide_format);

        fgetc(stdin);
    }
    
    //fclose(file_stream);

    return 0;
}

double bias_lower(double x)
{
    return (x - x * 0.05);
}

double bias_upper(double x)
{
    return (x + x * 0.05);
}

//Checking if boundary match the data format.
bool boundary_check(void)
{
    if((m % (DATA_WIDTH) == DATA_WIDTH-1) && m >= LOWER_WIDTH)
    {
        return true;
    }
    else
    {
        return false;
    }
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

//Sorting code buffer to take the format easier.
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

        //Return error when probing two more different value.
        if((code_buf[each + 1] - code_buf[each]) > (bias_upper(code[each]) - bias_lower(code[each])))
        {
            return false;
        }
    }
    wide_format = summation / (each - break_point);
    wide_bar = wide_format + 0.5;

    return true;
}

//Calibrating numbers of the code to format.
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

//Translating code from decimal to binary.
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

bool reverse_code(void)
{
    printf("|%d%d%d%d%d\n|", code[0], code[1], code[2], code[3], code[4]);
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