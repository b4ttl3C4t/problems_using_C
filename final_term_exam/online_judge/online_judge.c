#include <stdio.h>
#include <math.h>

#define problem_5 0



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

#define SIZE 31

typedef struct
{
	int x;
	int y;
} Point;

Point pt(int, int);
void visit(int[][SIZE], Point, unsigned int *);
void scan(FILE *, int[][SIZE], Point *start);
void print(int[][SIZE], unsigned int);

int main(void)
{
	FILE *fp = fopen("input1.txt", "r");
	Point start;
	int maze[SIZE][SIZE] = {0};
	int i, jewel = 0;
	
	start.x = start.y = 0;
	
	scan(fp, maze, &start);
	visit(maze, start, &jewel);
	print(maze, jewel);
	
	fclose(fp);
	return 0;
}

Point pt(int x, int y)
{
	Point p = {x, y};
	return p;
}

void visit(int maze[][SIZE], Point start, unsigned int *jewel)
{
	if (maze[start.x][start.y] == 4)
	{
		++*jewel;
		maze[start.x][start.y] = 0;
	}
	
	if (maze[start.x][start.y])
		return;
		
	maze[start.x][start.y] = 3;
	visit(maze, pt(start.x + 1, start.y), jewel);
	visit(maze, pt(start.x, start.y + 1), jewel);
	visit(maze, pt(start.x - 1, start.y), jewel);
	visit(maze, pt(start.x, start.y - 1), jewel);
}

void scan(FILE *fp, int maze[][SIZE], Point *start)
{
	int i, j;
	char ch;
	for (i = 0; i < SIZE; ++i)
	{
		for (j = 0; j < SIZE; ++j)
		{
			fscanf(fp, "%c", &ch);
			switch (ch)
			{
			case '.':
				maze[i][j] = 0;
				break;
			case 'X':
				maze[i][j] = 1;
				break;
			case '#':
				maze[i][j] = 2;
				break;
			case 'O':
				maze[i][j] = 4;
				break;
			}
			if (j == 0 && maze[i][j] == 0)
			{
				start->x = i;
				start->y = j;
			}printf("%c", ch);
		}printf("\n", ch);
		fgetc(fp);
	}printf("\n", ch);
}

void print(int maze[][SIZE], unsigned int jewel)
{
	int i, j;
	
	printf("Total jewel : %u\n", jewel);
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
			switch (maze[i][j])
			{
			case 0:
				printf(".");
				break;
			case 1:
				printf("X");
				break;
			case 2:
				printf("#");
				break;
			case 3:
				printf("@");
				break;
			case 4:
				printf("O");
				break;
			}
		printf("\n");
	}
	printf("\n");
}

#endif



#ifdef problem_6

int main(void)
{
	
}

#endif
