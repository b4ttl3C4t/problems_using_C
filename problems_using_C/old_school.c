#include <stdio.h>

void hanoi(unsigned int height, char from, char stagnent, char to)
{
    if(height == 1)
    {
        printf("from %c to %c\n", from, to);
    }
    else
    {
        hanoi(height - 1, from, to, stagnent);
        hanoi(1,          from, stagnent, to);
        hanoi(height - 1, stagnent, from, to);
    }   
}

// 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...
void fibonacci(unsigned int digit)
{
    unsigned int a = 0, b = 1, c, i;
    for(i = 0; i < digit - 2; ++i)
    {
        c = b + a;
        a = b;
        b = c;
    }
    printf("%u", c);
}

unsigned int permutation(unsigned int n, unsigned int m)
{
    unsigned int product = 1, i = 1;
    for(i = 1; i < m + 1; ++i)
    {
        product *= (n - i + 1);
    }
}

unsigned int combination(unsigned int n, unsigned int m)
{
    unsigned int product = 1, i = 1;
    for(i = 1; i < m + 1; ++i)
    {
        product = product * (n - i + 1) / i;
    }   //Don't write as "product *= (n - i + 1) / i;"
    
    return product;
}

//The function receives a parameter in [0, 12], composed of function "factorial" and "combination".
void pascal(unsigned int height)
{
    unsigned int i, j;
    for(i = 0; i < height + 1; ++i)
    {
        for(j = height - i + 1; j > 0; --j)
        {
            printf("   ");
        }
        for(j = 0; j < i + 1; ++j)
        {
            printf("%6u ", combination(i, j));
        }
        printf("\n");
    }
}

int main(void)
{
    printf("%u", permutation(1, 1));

    return 0;
}