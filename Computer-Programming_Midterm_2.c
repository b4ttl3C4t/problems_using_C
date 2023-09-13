#include <stdio.h>

void lab_1(int, int, int);
void lab_2(int);
void lab_3(int *);
void lab_4(void);
void lab_5(void);
void lab_6();

int main(void)
{	
	//lab_1(3,3,3);
}

void lab_1(int fore, int mid, int back)
{
    unsigned int i = 0, j = 0;

    for(i = 0; i < fore; ++i)
    {
        for(j = 0; j <= i; ++j)
        {
            printf("%d", i + 1);
        }
        printf("\n");
    }
    for(i = fore - 2; i > 0; --i)
    {
        for(j = 0; j <= i; ++j)
        {
            printf("%d", i + 1);
        }
        printf("\n");
    }

    for(i = 0; i < mid; ++i)
    {
        for(j = 0; j <= i; ++j)
        {
            printf("%d", i + 1);
        }
        printf("\n");
    }
    for(i = mid - 2; i > 0; --i)
    {
        for(j = 0; j <= i; ++j)
        {
            printf("%d", i + 1);
        }
        printf("\n");
    }

    for(i = 0; i < back; ++i)
    {
        for(j = 0; j <= i; ++j)
        {
            printf("%d", i + 1);
        }
        printf("\n");
    }
    /*for(i = back - 2; i >= 0; --i)
    {
        for(j = 0; j <= i; ++j)
        {
            printf("%d", i + 1);
        }
        printf("\n");
    }*/
}