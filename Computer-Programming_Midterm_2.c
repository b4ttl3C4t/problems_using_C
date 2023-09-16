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




/*lab_6.c*/
#define MESSAGE_SIZE 30
#define STR(x) #x
#define XSTR(x) STR(x)

void message_input( const unsigned int row, 
                    const unsigned int col, 
                    char str[][col][31]);
void message_handle(const unsigned int row, 
                    const unsigned int col, 
                    char str[][col][31]);
void output_result( char *, unsigned int);
void result_probe(  char *, unsigned int *);

void lab_6(void)
{
    char str[30][100][31] = {'\0'};
    unsigned int size, i, j, k, l;

    scanf("%u", &size);
    getchar();
    getchar();
    
    message_input(size, 100, str);
    message_handle(size, 100, str);
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

void message_input( const unsigned int row, 
                    const unsigned int col, 
                    char str[][col][31])
{
    char temp;
    unsigned int i, j;

    for(i = 0; i < row; ++i)
    {
        for(j = 0; j < col; ++j)
        {
            scanf("%"XSTR(MESSAGE_SIZE)"[a-zA-Z ][^\n]", str[i][j]);
            getchar();

            //handle the end of case (enter charactor '\n' twice).
            if((temp = getchar()) == '\n')
                break;
            else
                ungetc(temp, stdin);
        }
    }
}

void message_handle( const unsigned int row, 
                     const unsigned int col, 
                     char str[][col][31])
{
    unsigned int i, j;

    for(i = 0; i < row; ++i)
    {
        printf("Case #%u:\n", i + 1);
        for(j = 0; j < col; ++j)
        {
            if(strlen(str[i][j]) == 0)
                break;
            
            output_result(str[i][j], MESSAGE_SIZE);
        }
        puts("");
    }
}

inline void output_result(char *str, unsigned int length)
{
    unsigned int i = 0, j = 0, index = 1;

    putchar(str[0]);            //Print the first charactor and probe others.
    while(str[i] != '\0')       //(the first charactor would be printed out)
    {
        if(str[i] == ' ')
        {
            str += i + 1;       //Relocate array index to the next of white space.
            i = 0;
            result_probe(str, &index);
        }
        ++i;
    }
    puts("");
}

inline void result_probe(char *str, unsigned int *target)
{
    int j = 0;

    for(j = 0; j < *target; ++j)
    {
        if(str[j + 1] == ' ')   //Probe whether the next element of each one is white space.
        {                       //Bypass the word if its length is less than the index.
            return;
        }
    }
    putchar(str[j]);            //Has already passed the test so print it to monitor.
    ++*target;                  //Increasing index by one to update the value.
}