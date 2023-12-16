#include <stdio.h>
#include <math.h>

#define problem_4 0



#ifdef problem_1

int main(void)
{
    double a, b, c, s, area;

    scanf("%lf", &a);
    getchar();

    while(a >= 0)
    {
        scanf("%lf", &b);
        getchar();
        scanf("%lf", &c);
        getchar();

        s = (a+b+c) / 2;
        if(((s-a) <= 0) || ((s-b) <= 0) || ((s-c) <= 0))
        {
            printf("It is not a triangle!\n");
            scanf("%lf", &a);
            getchar();
            continue;
        }

        area = pow(s*(s-a)*(s-b)*(s-c), 0.5);
        printf("%.5lf\n", area);
        
        scanf("%lf", &a);
        getchar();
    }
}

#endif



#ifdef problem_2

int main(void)
{
    FILE *fp = fopen("predict.txt", "r");

    char option;
    char time;
    double mount;
    int factor;

    while(fscanf(fp, "%c %c %lf", &option, &time, &mount) == 3)
    {
    	fgetc(fp);
        if(option == 'A')
        {
            mount -= 1.25;
            factor = mount / 0.2;
            factor *= 5;

            if(time == 'N')
                printf("$%d\n", factor + 70);
            if(time == 'Y')
                printf("$%d\n", factor + 90);
            continue;
        }
        if(option == 'B')
        {
            if(time == 'N')
            {
                if(mount < 70)
                {
                    printf("You don't have enough money.\n");
                    continue;
                }
                mount -= 70;
                mount = mount / 5 * 0.2;
                printf("%.2lfkm\n", mount + 1.25);
            }
            if(time == 'Y')
            {
                if(mount < 90)
                {
                    printf("You don't have enough money.\n");
                    continue;
                }
                mount -= 90;
                mount = mount / 5 * 0.2;
                printf("%.2lfkm\n", mount + 1.25);
            }
        }
    }

    fclose(fp);
}

#endif



#ifdef problem_3

typedef struct
{
	double real;
	double imag;
} complex_t;

int main(void)
{
	int operation;
	complex_t foo, bar, result;
	
	scanf("%d", &operation);
	getchar();
	while(operation != -1)
	{
		scanf("%lf+%lfi", &(foo.real), &(foo.imag));
		getchar();
		scanf("%lf+%lfi", &(bar.real), &(bar.imag));
		getchar();
		switch(operation)
		{
			case 1:
				result.real = foo.real + bar.real;
				result.imag = foo.imag + bar.imag;
				break;
			case 2:
				result.real = foo.real - bar.real;
				result.imag = foo.imag - bar.imag;
				break;
			case 3:
				result.real = foo.real * bar.real - foo.imag * bar.imag;
				result.imag = foo.real * bar.imag + foo.imag * bar.real;
				break;
		}
		printf("%.2lf%+.2lfi\n", result.real, result.imag);
		scanf("%d", &operation);
		getchar();
	}
}

#endif



#ifdef problem_4

#define SIZE 6

// Bad method (?).
int main(void)
{
	int  pin[SIZE]  = {0};
	char str[1000] = {0};
	char ch;
	
	int count = 0, i = 0, j = 0;
	while(scanf("%c", &str[count]))
	{
		if((ch = getchar()) == '\n')
		{
			pin[j] = count;
			++j;
		}
		if(j == SIZE) break;
		++count;
	}
	
	for(i = 1; i < SIZE; ++i)
	{
		for(j = 0; j < count; ++j)
		{
			if(str[pin[i]] == str[j])
			{
				printf("True\n");
				break;
			}
		}
		if(j == count)
			printf("False\n");
	}
}

/*
D E F G H I
A B C G
J K H
L M J
N O P B
Q R S T U

*/

#endif



#ifdef problem_5

int main(void)
{
	
}

#endif



#ifdef problem_6

int main(void)
{
	
}

#endif
