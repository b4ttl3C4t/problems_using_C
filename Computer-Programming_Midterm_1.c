#include <stdio.h> 
#include <stdlib.h> 

void lab_1(int);
void lab_2(int);
void lab_3(int *);
void lab_4(void);
void lab_5(void);

int main(void)
{	
	lab_5();
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

	//test data: int arr[10] = {10, 15, 23, 15, 55, 75, 55, 15, 55, 1112};
}

void lab_4(void)
{
	unsigned int length = 4, i, j, k;
	
	printf("input:");
	scanf("%u", &length);

	int X[8][8] = {0}, Y[8][8] = {0}, product[8][8] = {0};
	
	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < length; ++j)
		{
			scanf("%d", &X[i][j]);
		}
	}

	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < length; ++j)
		{
			scanf("%d", &Y[i][j]);
		}
	}

	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < length; ++j)
		{
			for(k = 0; k < length; ++k)
			{
				product[i][k] += X[i][j] * Y[j][k];
			}
		}
	}
	
	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < length; ++j)
		{
			printf("%d ", product[i][j]);
		}
		printf("\n");
	}
/*input: 
4
1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31
0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
*/
}

void lab_5(void)
{
	unsigned int each = 0, length = 4, i, j, k;
	
	printf("input:");
	scanf("%u", &each);
	scanf("%u", &length);

	int X[10][8][8] = {0}, addition[8][8] = {0};
	
	for(i = 0; i < each; ++i)
	{
		for(j = 0; j < length; ++j)
		{
			for(k = 0; k < length; ++k)
			{
				scanf("%d", &X[i][j][k]);
			}
		}
	}

	for(i = 0; i < each; ++i)
	{
		for(j = 0; j < length; ++j)
		{
			for(k = 0; k < length; ++k)
			{
				addition[j][k] += X[i][j][k];
			}
		}
	}
	
	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < length; ++j)
		{
			printf("%d ", addition[i][j]);
		}
		printf("\n");
	}
/*input: 
2
4
1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31
0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
*/
}
