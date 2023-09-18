#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lab_1(int, int, int);
void lab_2();

int main(void)
{
    lab_2();
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

/*lab_2*/
typedef struct LINKED_LIST
{
	double x;
	double y;
	struct LINKED_LIST *pre;
	struct LINKED_LIST *next;
}linked_list;

void convert(linked_list *, float[][2], int);
void sort(linked_list *, int);
linked_list * index_list(linked_list *, int);
void print_list(linked_list *);
/*請使用雙項鍊表才能改變該程式使其能夠運行（以利節點交換）*/
void lab_2()
{
	int size = 5;
	float data[][2] =
	{
		{1.2, 3.7}, {5.98, 7.75}, 
		{10.13, 7.75}, {-7.51, -3.7}, 
		{1.2, -6.23}
	};

	linked_list head;
	head.x = 0.0;
	head.y = 0.0;
	head.pre = NULL;
	head.next = NULL;
	convert(&head, data, size);
	//sort(&head, size);
	print_list(&head);
}

void convert(linked_list *list, float data[][2], int size)
{
	int i;

	linked_list *head = list;

	for(i = 0; i < size; ++i)
	{
		list->x = data[i][0];
		list->y = data[i][1];

		list->next = (linked_list *)malloc(sizeof(linked_list));
		list->next->pre  = list;
		list->next->next = head;
		head->pre = list->next;
		printf("%.2f %.2f\n", list->next->x, list->next->y);

		list = list->next;
	}
	list->next = head;
}

void sort(linked_list *list, int size)
{
	int i, j;

	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < size; ++j)
		{
			if(index_list(list, j)->x > index_list(list, j + 1)->x)
			{
				index_list(list, j)->pre->next = index_list(list, j + 1);
				index_list(list, j)->next = index_list(list, j + 2);

				index_list(list, j + 1)->next->pre  = index_list(list, j);
				index_list(list, j + 1)->pre = index_list(list, j - 1);
			}
			printf("%d %d\n", i, j);
		}
	}
}

inline linked_list * index_list(linked_list *list, int index)
{
	int i;

	for(i = 0; i < index; i++)
	{
		list = list->next;
	}
	return list;
}

inline void print_list(linked_list *list)
{
	linked_list *head = list;
	for(; list->next != head; list = list->next)
	{
		printf("%.2f %.2f\n", list->x, list->y);
	}

	printf("\n");

	list = head->pre;
	for(; list->pre != head; list = list->pre)
	{
		printf("%.2f %.2f\n", list->x, list->y);
	}
}