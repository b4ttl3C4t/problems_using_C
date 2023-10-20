#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void ScrollingSign(void);
static void AnEasyProblem(void);
static void MagicFormula(void);
static void SymmetricMatrix(void);
static void ContinuedFractions(void);
static void PrimaryArithmetic(void);
static void AMinimumLandPrice(void);

int main(void)
{
    AMinimumLandPrice();

    return 0;
}

static void ScrollingSign(void)
{
    unsigned int n, i, j, k;
    unsigned int left, right, __union__;

    char buf[100][100] = {'\0'};
    
    scanf("%u", &n);
    getchar();

    for(i = 0; i < n; ++i)
    {
        scanf("%u", &left);
        getchar();
        scanf("%u", &right);
        getchar();
        __union__ = 0;

        for(j = 0; j < right; ++j)
        {
            for(k = 0; k < left; ++k)
            {
                scanf("%c", &buf[j][k]);
            }
            getchar();
        }

        __union__ = strlen(buf[0]);
        for(j = 1; j < __union__; ++j)
        {
            if(strncmp(buf[0] + j, buf[1], __union__ - j))
            {
                __union__ = __union__ - j;
                break;
            }
        }

        __union__ = left + (__union__) * (right - 1);
        printf("%u", __union__);

        for(j = 0; j < right; ++j)
        {
            for(k = 0; k < left; ++k)
            {
                buf[j][k] = '\0';
            }
        }
    }
}

static void AnEasyProblem(void)
{
    char ch;
    char table[100] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int  d_table[100] = {0};

    for(int i = 0; i < 100; ++i)
    {
        d_table[i] = i + 1;
    }

    for(int i = 0; i < 3; ++i)
    {
        scanf("%c", &ch);
        getchar();

        for(int j = 0; j < 100; ++j)
        {
            if(table[j] == ch)
            {
                printf("%d\n", d_table[j]);
                break;
            }
        }
    }
}

static void MagicFormula(void)
{
    int a, b, c, d, L;
    unsigned int count, i, result;

    while(1)
    {
        count = 0;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &L);

        if(a == 0 && b == 0 && c == 0 && d == 0 && L == 0 )
        {
            break;
        }

        for(i = 0; i <= L; ++i)
        {
            result = a*i*i + b*i + c;
            if(result % d == 0)
            {
                ++count;
            }
        }
        printf("%u\n", count);
    }
}

static void SymmetricMatrix(void)
{
    int matrix[100][100] = {0};
    unsigned int i, j;
    unsigned int left, right;

    unsigned int number, N;
    scanf("%u", &number);
    getchar();

    while(number--)
    {
        scanf("N = %u", &N);
        getchar();

        for(i = 0; i < N; ++i)
        {
            for(j = 0; j < N; ++j)
            {
                scanf("%u", &matrix[i][j]);
            }
            getchar();
        }

        for(left = 0, right = N - 1; left < right; ++left, --right)
        {
            for(j = 0; j < N; ++j)
            {
                if(matrix[left][j] != matrix[right][N - 1 - j])
                {
                    printf("%s\n", "Non-symmetric");
                    goto BREAK;
                }
            }
        }
        printf("%s\n", "Symmetric");

BREAK:
        for(i = 0; i < N; ++i)
        {
            for(j = 0; j < N; ++j)
            {
                matrix[i][j] = 0;
            }
        }
    }
}

static void ContinuedFractions(void)
{
    unsigned int N, firstFlag;
    unsigned int numerator, denominator, quotient, remainder;
    unsigned int i;

    scanf("%u", &N);
    getchar();
    for(i = 0; i < N; ++i)
    {
        firstFlag = 1;
        scanf("%u%u", &numerator, &denominator);
        
        printf("%c", '[');
        while(1)
        {
            quotient    = numerator / denominator;
            remainder   = numerator % denominator;
            numerator   = denominator;
            denominator = remainder;

            printf("%u", quotient);

            if(remainder == 0)
                break;

            if(firstFlag)
            {
                firstFlag = 0;
                printf("%c", ';');
                continue;
            }
            printf("%c", ',');
        }
        printf("%c", ']');
    }
}

static int char2int(char ch)
{
    return ch - '0';
}

static void PrimaryArithmetic(void)
{
    char op1[10] = {0}, op2[10] = {0};
    unsigned int carry, i, count, flag;

    scanf("%s %s", op1, op2);
    getchar();

    while(op1[0]!='0' || op2[0]!='0')
    {
        for(i = 0, count = 0; i < 10; ++i)
        {
            carry = flag = 0;

            carry += flag;
            if(op1[i] != '\0')
                carry += char2int(op1[i]);
            if(op2[i] != '\0')
                carry += char2int(op2[i]);
            flag = carry >= 10;

            if(flag)
            {
                ++count;
            }
        }

        if(!count)
        {
            printf("No carry operation.\n");
        }
        if(count == 1)
        {
            printf("1 carry operation.\n");
        }
        if(count > 1)
        {
            printf("%u carry operations.\n", count);
        }
        
        scanf("%s %s", op1, op2);
        getchar();
    }
}

static void sort(unsigned int *arr)
{
    static unsigned int i, j, temp;
    
    for(i = 0; i < 40; ++i)
    {
        for(j = 0; j < 39; ++j)
        {
            if(arr[j] > arr[j + 1])
            {
                temp    = arr[j];
                arr[j]  = arr[j+1];
                arr[j+1]= temp;
            }
        }
    }
}

static unsigned long long int my_pow(unsigned int n, unsigned int count)
{
    static long long int i, base;

    for(i = 0, base = n; i < count; ++i)
    {
        n *= base;
    }

    return n;
}

static void AMinimumLandPrice(void)
{
    unsigned int buf[40];
    unsigned int T, i, j, count;
    unsigned int budget;

    scanf("%u", &T);
    getchar();

    for(i = 0; i < T; ++i)
    {
        budget = count = 0;

        for(j = 0; j < 40; ++j)
        {
            buf[j] = 0;
        }

        for(j = 0; j < 40; ++j)
        {
            scanf("%u", &buf[j]);
            getchar();

            if(buf[j] == 0)
            {
                break;
            }
        }
        sort(buf);
        
        for(j = 39; j >= 0; --j)
        {
            if(buf[j] == 0)
            {
                break;
            }
            
            budget += 2 * my_pow(buf[j], count);
            ++count;
        }

        if(budget > 5000000)
        {
            printf("Too expensive\n");
        }
        else
        {
            printf("%u\n", budget);
        }
    }
}