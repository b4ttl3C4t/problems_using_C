#include <stdio.h> 
#include <stdlib.h> 

struct Matrix 
{
	int **data;
	unsigned int length;
};

void malloc_matrix(struct Matrix *, unsigned int);
void scanf_matrix(struct Matrix *, unsigned int);
void print_matrix(struct Matrix *, unsigned int);

void lab_1(int);
void lab_2(int);
void lab_3(int *);
void lab_4(struct Matrix *, struct Matrix *, unsigned int);

int main(void)
{
	int arr[10] = {10, 15, 23, 15, 55, 75, 55, 15, 55, 1112};
	int length = 4;
	
	struct Matrix X, Y;
	malloc_matrix(&X, length);
	malloc_matrix(&Y, length);
	scanf_matrix(&X, length);
	print_matrix(&X, length);
	lab_4(&X, &Y, 4);
}

void malloc_matrix(struct Matrix *X, unsigned int length)
{
	X->data = (int **)calloc(length, sizeof(int **));
	
	int i;
	for(i = 0; i < length; ++i)
	{
		X->data[i] = (int *)calloc(length, sizeof(int *));
	}
}

void scanf_matrix(struct Matrix *X, unsigned int length)
{
	int i, j;
	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < length; ++j)
		{
			scanf("%d", X->data[i][j]);
		}
	}
	/*1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31
	  0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30*/
}

void print_matrix(struct Matrix *X, unsigned int length)
{
	int i, j;
	
	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < length; ++j)
		{
			printf("%d ", X->data[i][j]);
		}
		printf("\n");
	}
}

void lab_1(int height)
{
	int i, j;
	
	for(i = 0; i < height; ++i)
	{
		
		for(j = 0; j < i; ++j)
			printf(" ");
			
		for(j = height + 1; j > i + 1; --j)
			printf("*");
			
		for(j = i; j < height - 1; ++j)
			printf("*");
			
		printf("\n");
	}
	
	for(i = 1; i < height; ++i)
	{
		for(j = i; j < height - 1; ++j)
			printf(" ");
			
		for(j = 0; j < i + 1; ++j)
			printf("*");
			
		for(j = 0; j < i; ++j)
			printf("*");
				
		printf("\n");
	}
}

void lab_2(int number)
{
	int i;
	
	for(i = 0; i < 100; ++i)
	{
		if(number % 5 == 0)
			number /= 5;
	}
	
	for(i = 0; i < 100; ++i)
	{
		if(number % 3 == 0)
			number /= 3;
	}
	
	for(i = 0; i < 100; ++i)
	{
		if(number % 2 == 0)
			number /= 2;
	}
	
	printf("%s", number - 1? "It is not an ugly number.": "It is an ugly number.");
}

void lab_3(int *arr)
{
	int i, j, summation = 0;
	int flag[10] = {0};
	
	for(i = 0; i < 10; ++i)
	{
		for(j = 0; j < 10; ++j)
		{
			if(i == j)
				break;
			
			if(arr[i] == arr[j])
				flag[i] = 1;
				
			if(flag[j] == 1)
				flag[i] = 0;
		}
	}
	
	for(i = 0; i < j; ++i)
	{
		if(flag[i] == 1)
		{
			summation += arr[i];
		}
	}
	printf("%d", summation);
}

void lab_4(struct Matrix *X, struct Matrix *Y, unsigned int length)
{
	int i, j, k;
	
	struct Matrix result;
	malloc_matrix(&result, length);
	
	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < length; ++j)
		{
			for(k = 0; k < length; ++k)
			{
				result.data[i][k] += X->data[i][j] * Y->data[j][k];
			}
		}
	}
	print_matrix(&result, length);
}