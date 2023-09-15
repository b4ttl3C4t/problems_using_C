#include <stdio.h>
#include <string.h>

#define SWAP(x, y)          \
        temp = (x);         \
        (x) = (y);          \
        (y) = temp;         \

void lab_1(int, int, int);
void lab_2(void);
void lab_3(void);
void lab_4(void);
void lab_5(void);
void lab_6(void);

int main(void)
{
	lab_6();
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
    for(i = back - 2; i > 0; --i)
    {
        for(j = 0; j <= i; ++j)
        {
            printf("%d", i + 1);
        }
        printf("\n");
    }
    printf("1");
}

void lab_2(void)
{
    unsigned int legnth = 0, i, j;
    double temp, arr[10][2] = {0.0};

    scanf("%u", &legnth);

    for(i = 0; i < legnth; ++i)
    {
        for(j = 0; j < 2; ++j)
        {
            scanf("%lf", &arr[i][j]);
        }
    }

    for(i = 0; i < legnth - 1; ++i)
    {
        for(j = 0; j < legnth - 1; ++j)
        {
            if(arr[j][1] > arr[j + 1][1])
            {
                SWAP(arr[j][1], arr[j + 1][1]);
            }
        }
    }
    for(i = 0; i < legnth - 1; ++i)
    {
        for(j = 0; j < legnth - 1; ++j)
        {
            if(arr[j][0] > arr[j + 1][0])
            {
                SWAP(arr[j][0], arr[j + 1][0]);
            }
        }
    }

    for(i = 0; i < legnth; ++i)
    {
        for(j = 0; j < 2; ++j)
        {
            printf("%.2f ", arr[i][j]);
        }
        printf("\n");
    }

    /*test data:
5
1.2 3.7
5.98 7.75
10.13 7.75
-7.51 -3.7
1.2 -6.23
    */
}

/*There is the cipher function, written in func.h .*/
void Caesar_Cipher(char *arr, int length, int offset)
{
    unsigned int i;

    for(i = 0; i < length; ++i)
    {
        if (arr[i] >= 'A' && arr[i] <= 'Z')
        {
            arr[i] =  'A' + ((arr[i] - 'A') + offset) % 26;
        }
        if (arr[i] >= 'a' && arr[i] <= 'z')
        {
            arr[i] =  'a' + ((arr[i] - 'a') + offset) % 26;
        }
    }
}

void lab_3(void)
{
    int offset = 0;
    char str[150] = {0};
    
    scanf("%100[^\n]", str);
    getchar();
    scanf("%d", &offset);
    str[strlen(str)] = '\0';
    Caesar_Cipher(str, strlen(str), offset);
    printf("%s", str);

    /*
Hello world!
4
    */
}

void lab_4(void)
{
    char str[50];
}

void lab_5(void)
{
    char str[50];
}

void lab_6(void)
{
    
    char temp, str[30][100][31] = {'\0'};
    unsigned int size, i, j, k, l;

    scanf("%u", &size);
    getchar();
    getchar();

    for(i = 0; i < size; ++i)
    {
        for(j = 0; j < 100; ++j)
        {
            scanf("%30[a-zA-Z ][^\n]", str[i][j]);
            getchar();

            if((temp = getchar()) == '\n')
                break;
            else
                ungetc(temp, stdin);
        }
    }
    
    unsigned int flag = 0, length = 0;
    for(i = 0; i < size; ++i)
    {
        printf("Case #%u:\n", i + 1);
        for(j = 0; j < 100; ++j)
        {
            length = strlen(str[i][j]);
            flag = 0;

            if(length == 0)
                break;
            
            for(k = 0; k < 30; ++k)
            {
                if(str[i][j][k] == ' ')
                {
                    k += flag;
                    flag += 1;
                    puts("");
                }
                if(k == flag)
                putchar(str[i][j][k]);
            }
        }
        printf("\n");
    }
    
    /*
test data:
2

Hey good lawyer
as I previously previewed
yam does a soup

First I give money to Teresa
after I inform dad of
your borrible soup
    */
}