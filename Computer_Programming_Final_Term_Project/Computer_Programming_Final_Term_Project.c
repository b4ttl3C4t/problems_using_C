#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BUF_SIZE    150
#define DATA_WIDTH  5
#define LOWER_WIDTH 29
#define SWAP(x, y)  (x) = (x) ^ (y);    \
                    (y) = (x) ^ (y);    \
                    (x) = (x) ^ (y);

typedef struct data_s
{
    char each[5];
} data_t;

static int32_t  code        [BUF_SIZE] = {0};
static int32_t  code_buf    [BUF_SIZE] = {0};
static int32_t  data        [BUF_SIZE] = {0};
static int32_t  data_index, each, i, j;
static double   narrow_format, wide_format;

void            scan_code       (/*FILE *,*/ int32_t);
void            sort_code       (int32_t);
inline double   bias_lower      (double);
inline double   bias_upper      (double);
bool            take_format     (int32_t);
inline bool     calibrate_bias  (int32_t);
int32_t         raw_data        (int32_t);
int32_t         reverse_data    (int32_t);
inline bool     boundary_check  (int32_t);
inline bool     split_check     (int32_t);
inline bool     C_check         (int32_t [], int32_t);
inline bool     K_check         (int32_t [], int32_t);
inline bool     decode_table    (data_t *);
inline int32_t  code_weight     (data_t *);

int main(void)
{
    int32_t m, count = 0;
    FILE *file_stream;
    
    //file_stream = fopen("test.txt", "r+");
    while(1){
        ++count;
        fscanf(stdin, "%d", &m);
        fgetc(stdin);
        
        if(m == 0)
        {
            break;
        }

        if(!boundary_check(m))
        {
            printf("#Case%d : bad code\n", count);
            continue;
        }

        scan_code(m);
        sort_code(m);
        
        if(!take_format(m))
        {
            printf("#Case%d : bad code\n", count);
            continue;
        }
        
        calibrate_bias(m);

        printf("%lf %lf\n", narrow_format, wide_format);

        fgetc(stdin);
    }
    
    //fclose(file_stream);

    return 0;
}

void scan_code(/*FILE * file_stream,*/ int32_t m)
{
    for(each = 0; each < m; ++each)
    {
        fscanf(stdin, "%d", &code[each]);
        getc(stdin);

        code_buf[each] = code[each];
    }
}

void sort_code(int32_t m)
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

double bias_lower(double x)
{
    return (x - x * 0.05);
}

double bias_upper(double x)
{
    return (x + x * 0.05);
}

bool take_format(int32_t m)
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
            break;
        }
    }

    summation = 0.0;
    ++each;
    break_point = each + 1;
    for(; each < m - 1; ++each)
    {
        summation += code_buf[each];
        if((code_buf[each + 1] - code_buf[each]) > (bias_upper(code[each]) - bias_lower(code[each])))
        {
            return 0;
        }
    }
    wide_format = summation / (each - break_point);

    return 1;
}

bool boundary_check(int32_t m)
{
    if((m % (DATA_WIDTH + 1) == DATA_WIDTH) && m >= LOWER_WIDTH)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

inline bool calibrate_bias(int32_t m)
{
    for(each = 0; each < m; ++each)
    {
        if( bias_lower(narrow_format) < code[each] || 
            bias_upper(narrow_format) > code[each])
        {
            code[each] = narrow_format + 0.5;
            continue;
        }

        if( bias_lower(wide_format) < code[each] ||
            bias_upper(wide_format) > code[each])
        {
            code[each] = wide_format + 0.5;
            continue;
        }

        return 0;
    }

    for(each = 0; each < m - 1; ++each)
    {
        printf("%d ", code[each]);
    }

    return 1;
}