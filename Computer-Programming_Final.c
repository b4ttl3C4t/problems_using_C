#include <stdio.h>
#include <string.h>

void lab_1(int, int, int);

int main(void)
{
    lab_1(5, 3, 5);
    return 0;
}

/*lab_1*/
int  max(int, int, int);
void print_knot(int, int, int);

void lab_1(int fore, int mid, int back)
{
    int i, j, weight = max(fore, mid, back);
    
	print_knot(fore, weight, 0);
	print_knot(mid, weight, 1);
	print_knot(back, weight, 0);
}

inline int max(int x, int y, int z)
{
	int maximum = 0;
	
	if(x >= y && x >= z)
		maximum = x;
	else if(y >= x && y >= z)
		maximum = y;
	else
		maximum = z;
	
	return maximum;
}

void print_knot(int current, int weight, int is_mid)
{
	int i, j;
	
	is_mid = (is_mid)? 1: 0;
	current = (current + 1) / 2;
	for(i = 1 + is_mid; i <= current; ++i)
	{
		for(j = current; j <= weight - current; j = j + 2)
			printf(" ");
		for(j = 1; j <= current - i; ++j)
			printf(" ");
		for(j = 1; j <= 1 + 2 * (i - 1); ++j)
			printf("%1d", 1 + 2 * (i - 1));
		printf("\n");
	}
	for(i = current - 1; i >= 1 + is_mid; --i)
	{
		for(j = current; j <= weight - current; j = j + 2)
			printf(" ");
		for(j = current - i; j >= 1; --j)
			printf(" ");
		for(j = 1 + 2 * (i - 1); j >= 1; --j)
			printf("%1d", 1 + 2 * (i - 1));
		printf("\n");
	}
}