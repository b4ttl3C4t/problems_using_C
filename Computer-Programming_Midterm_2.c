#include <stdio.h>
#include <string.h>

void lab_1(int, int, int);
void lab_2(void);
void lab_3(void);
void lab_4(void);
void lab_5(void);
void lab_6(void);

int main(void)
{
	lab_4();
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



#define SWAP(x, y)          \
        temp = (x);         \
        (x) = (y);          \
        (y) = temp;         \

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

    /* test data:
5
1.2 3.7
5.98 7.75
10.13 7.75
-7.51 -3.7
1.2 -6.23
    */
}



/*lab_3*/
void Caesar_Cipher(char *, int, int);

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

    /* test data:
Hello world!
4
    */
}

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



/*lab_4*/
#define STR_SIZE 50
#define RESULT_SIZE 100

void find_location(char *, int *, int *, int *, char *);
void concatenation(char *, int, int, char *);

void lab_4(void)
{
    char str    [RESULT_SIZE + 1];
    char orig   [STR_SIZE + 1];
    char replace[STR_SIZE + 1];
    int  index = 0, start = 0, end = 1;

    gets(str);
    gets(orig);
    gets(replace);
    
    while(1)
    {
        find_location(str, &index, &start, &end, orig);
        if(index == RESULT_SIZE)
            break;
        concatenation(str, start, end, replace);
    }
    puts(str);

    /* test data:
Hello world!
world
C Programming
    */
}

/*Setting location for start and end of keyword, 
 *and updating index at the same time.
 */
void find_location(char *str, int *index, int *start, int *end, char *orig)
{
    int length = strlen(orig);

    for (; *index < RESULT_SIZE; ++*index)
    {
        if(!strncmp(str + *index, orig, length))
        {
            *start  = *index;
            *end    = *index + length;
            return;
        }
    }
}

/*Splitting string by place1 and place2, 
 *and inserting string which you want to replace the original one.
 */
void concatenation(char *str, int place1, int place2, char *insert)
{
    char buf1 [STR_SIZE + 1];
    char buf2 [STR_SIZE + 1];

    str[place1] = '\0';
    sprintf(buf1, "%s", str);
    sprintf(buf2, "%s", str + place2);
    sprintf(str, "%s%s%s", buf1, insert, buf2);
}

#undef STR_SIZE
#undef RESULT_SIZE



/*lab_5*/
void lab_5(void)
{
    char str[50];
}



/*lab_6*/
#define MESSAGE_SIZE 30
#define STR(x)  #x          //Trick: Scanning macro twice to assure the result accepted.
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
    /* test data:
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
            /*It will trans to "%30[a-zA-Z ][^\n]" ,
             *which means you should input 30 charactor
             *between 'a' to 'z', 'A' to 'Z' or white space
             *and input '\n' (enter button) to end the string.
             */
            //You can replace function scanf(...) by gets(char *) to make it more clear.
            getchar();

            //Handling the end of case (when you input charactor '\n' twice).
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
            /*Out of current loop when there is no string there.
             *(Namely, length of string is zero.)
             */
            if(strlen(str[i][j]) == 0)
                break;
            
            output_result(str[i][j], MESSAGE_SIZE);
        }
        puts("");
    }
}

inline void output_result(char *str, unsigned int length)
{
    unsigned int i = 0, index = 1;

    putchar(str[0]);
    /*Printing out the first charactor and probe others.
     *(The first charactor would be printed out.)
     */
    while(str[i] != '\0')        
    {
        if(str[i] == ' ')
        {
            str += i + 1;       //Relocating array index to the next of white space.
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
        if(str[j + 1] == ' ')   //Probing whether the next element of each one is white space.
        {                       //Bypass the word if its length is less than the index.
            return;
        }
    }
    putchar(str[j]);            //The word has already passed the test so print it out.
    ++*target;                  //Increasing index by one to update the value.
}

#undef MESSAGE_SIZE
#undef STR
#undef XSTR