#include "Computer_Programming_Final_Term_Project.h"

#define CODE_SIZE   150
#define DATA_WIDTH  5
#define LOWER_WIDTH 29
#define METHOD_STEP 7
#define SWAP(x, y)  (x) = (x) ^ (y);    \
                    (y) = (x) ^ (y);    \
                    (x) = (x) ^ (y);

static int32_t  code        [CODE_SIZE] = {0};
static int32_t  code_buf    [CODE_SIZE] = {0};
static char     data        [CODE_SIZE] = {'\0'};

static int32_t  each, i, j;
static int32_t  count, m;

static double   narrow_format, wide_format;
static int32_t  narrow_bar,    wide_bar;

static inline int32_t  code_weight     (int32_t *);
static inline double   bias_lower      (double);
static inline double   bias_upper      (double);

bool (*method[METHOD_STEP])(void) = 
{
    scan_code, 
    sort_code, 
    take_format, 
    calibrate_code, 
    binary_code, 
    //reverse_code, 
    //get_data
};

int main(void)
{
    //FILE *file_stream = fopen("test.txt", "r");
    
    while(1)
    {
        ++count;
        fscanf(stdin, "%d", &m);
        fgetc(stdin);
        
        if(m == 0)
        {
            break;
        }

        if(!boundary_check())
        {
            printf("#Case%d : bad code\n", count);
            continue;
        }

        scan_code();
        sort_code();
        take_format();
        calibrate_code();
        binary_code();
        
        if(!take_format())
        {
            printf("#Case%d : bad code\n", count);
            continue;
        }

        if(!calibrate_code())
        {
            printf("#Case%d : bad code\n", count);
            continue;
        }
        binary_code();
        
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

bool boundary_check(void)
{
    if((m % (DATA_WIDTH + 1) == DATA_WIDTH) && m >= LOWER_WIDTH)
    {
        return true;
    }
    else
    {
        return false;
    }
}

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