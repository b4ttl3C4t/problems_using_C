#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void ScrollingSign(void);
static void AnEasyProblem(void);

int main(void)
{
    AnEasyProblem();

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