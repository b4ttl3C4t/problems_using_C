#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



/*lab_1*/
int  max(int, int, int);
void print_knot(int, int, int);

void lab_1(int fore, int mid, int back)
{
    int weight = max(fore, mid, back);
    
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

void lab_2_convert(linked_list *, float[][2], int);
void sort(linked_list *, int);
void print_list(linked_list *);
void data_swap(linked_list *, linked_list *);
linked_list * index_list(linked_list *, int);

void lab_2(void)
{
	int size = 5;
	float data[][2] =
	{
		{1.2, 3.7}, {5.98, 7.75}, 
		{10.13, 7.75}, {-7.51, -3.7}, 
		{1.2, -6.23}
	};

	linked_list head;
	lab_2_convert(&head, data, size);
	sort(&head, size);
	print_list(&head);
}

void lab_2_convert(linked_list *list, float data[][2], int size)
{
	int i;

	//You should set the data to head node firstly.
	linked_list *head = list;
	head->pre 	= NULL;
	head->next 	= NULL;
	head->x		= data[0][0];
	head->y 	= data[0][1];

	//Then, you can add nodes connecting head node to construct the whole linked list.
	for(i = 1; i < size; ++i)
	{
		/*Allocating memory for the newer node, 
		 *and concatenating the newer node with the head node and the last node.
		 */
		list->next = (linked_list *)malloc(sizeof(linked_list));
		head->pre 	= list->next;

		//Setting the data of the newer node (including x, y, pre and next).
		list->next->x 		= data[i][0];
		list->next->y 		= data[i][1];
		list->next->pre  	= list;
		list->next->next 	= head;
		
		//To the next node.
		list = list->next;
	}
}

void sort(linked_list *list, int size)
{
	int i, j;

	for(i = 0; i < size - 1; ++i)
	{
		for(j = 0; j < size - 1; ++j)
		{
			if(index_list(list, j)->y > index_list(list, j + 1)->y)
			{
				data_swap(index_list(list, j), index_list(list, j + 1));
			}
		}
	}

	for(i = 0; i < size - 1; ++i)
	{
		for(j = 0; j < size - 1; ++j)
		{
			if(index_list(list, j)->x > index_list(list, j + 1)->x)
			{
				data_swap(index_list(list, j), index_list(list, j + 1));
			}
		}
	}
}

inline void data_swap(linked_list *X, linked_list *Y)
{
	static float temp;

	temp = X->x;
	X->x = Y->x;
	Y->x = temp;

	temp = X->y;
	X->y = Y->y;
	Y->y = temp;
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
	
	do
	{
		printf("%.2f %.2f\n", list->x, list->y);
		list = list->next;
	} while (list != head);
}



/*lab_3*/
#define NAME_SIZE 50
#define STR(x) #x
#define XSTR(x) STR(x)

typedef struct GRADE_LIST
{
	int English;
	int Math;
	int History;
	int Physics;
	char name[NAME_SIZE + 1];
	struct GRADE_LIST *pre;
	struct GRADE_LIST *next;
}grade_list;

void 	lab_3_convert(grade_list *, char *, int);
double 	average(grade_list *);
int 	input_data(grade_list *, char *, int);
void 	print_data(grade_list *);

void lab_3(void)
{
	char* data = 
		"Caspar Murray,50,25,100,80\n"
		"Rory Gordon,50,50,100,60\n"
		"Winnie Randolph,50,100,50,20\n";
	
	char foo[1001] = {0};

	sprintf(foo, "%s", data);
	grade_list head;
	head.pre  = NULL;
	head.next = NULL;

	lab_3_convert(&head, data, 3);
	print_data(&head);
}

void lab_3_convert(grade_list *list, char *data, int length)
{
	int index = 0;
	grade_list *head = list;
	index = input_data(head, data, index);

	for(int i = 1; i < length; ++i)
	{
		list->next = (grade_list *)malloc(sizeof(grade_list));
		head->pre  = list->next;

		index = input_data(list->next, data, index);
		list->next->pre  = list;
		list->next->next = head;
		
		list = list->next;
	}
}

double average(grade_list *list)
{
	grade_list *head = list;
	int summation = 0, length = 0;

	do
	{
		summation += list->English + list->Math + list->History + list->Physics; 
		++length;
		list = list->next;
	} while (list != head);

	return summation / length;
}

int input_data(grade_list *list, char *data, int index)
{
	sscanf(data + index, "%"XSTR(NAME_SIZE)"[^,]%*c%d%*c%d%*c%d%*c%d",
		list->name,
		&list->English,
		&list->Math,
		&list->History,
		&list->Physics);
	
	do
	{
		++index;
	} while (data[index] != '\n');
	/*You have to return the index with increasing one
	 *to avoid the first charactor '\n' .
	 *Otherwise, there are going to get a *new line* to the element *name* .
	 */
	return ++index;
}

void print_data(grade_list *list)
{
	grade_list *head = list;
	
	do
	{
		printf("%s: %d, %d, %d, %d\n", list->name, list->English, list->Math, list->History, list->Physics);
		list = list->next;
	} while (list != head);
	
	printf("Average score: %.2lf\n", average(head));
}

#undef NAME_SIZE
#undef STR
#undef XSTR



/*lab_4*/
void lab_4(void)
{

}



/*lab_5*/
#define BUF_SIZE 30
#define STR(x) #x
#define XSTR(x) STR(x)

char letter_to_number_table(char, unsigned int *, unsigned int *);

void lab_5(void)
{
	//The buffer for data input.
	char data[2000][BUF_SIZE + 1] = {'\0'};
	//For size and loop.
	unsigned int i, j, length = 0;
	//Handling the content of data by letter-to-number table.
	unsigned int letters, hyphens;

	scanf("%u", &length);
	getchar();

	for(i = 0; i < length; ++i)
	{
		scanf("%"XSTR(BUF_SIZE)"[0-9A-Z-][^\n]", data[i]);
		getchar();
	}

	for(i = 0; i < length; ++i)
	{
		letters = hyphens = 0;

		for(j = 0; j < BUF_SIZE; ++j)
		{
			if(!data[i][j])
				break;
			putchar(letter_to_number_table(data[i][j], &letters, &hyphens));
		}
		printf(" %u %u", letters, hyphens);
		putchar('\n');
	}

	/*test data:
2
1-HOME-SWEET-HOME
MY-MISERABLE-JOB
	*/
}

char letter_to_number_table(char c, unsigned int *letter_flag, unsigned int *hyphen_flag)
{
	switch(c)
	{
	case 'A':
	case 'B':
	case 'C':
		c = '2';
		break;

	case 'D':
	case 'E':
	case 'F':
		c = '3';
		break;

	case 'G':
	case 'H':
	case 'I':
		c = '4';
		break;
		
	case 'J':
	case 'K':
	case 'L':
		c = '5';
		break;
		
	case 'M':
	case 'N':
	case 'O':
		c = '6';
		break;
			
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
		c = '7';
		break;

	case 'T':
	case 'U':
	case 'V':
		c = '8';
		break;
			
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
		c = '9';
		break;
	
	case '-':
		++*hyphen_flag;
		return c;
	
	default:
		return c;
	}
	
	++*letter_flag;
	return c;
}

#undef BUF_SIZE
#undef STR
#undef XSTR



/*lab_6*/
#define BUF_SIZE 75
#define STR(x) #x
#define XSTR(x) STR(x)

void		 name_sort(char (*)[BUF_SIZE + 1], unsigned int);
static void  name_swap(char *, char *);
unsigned int name_count(char (*)[BUF_SIZE + 1], unsigned int *, unsigned int);
void 		 name_print(char (*)[BUF_SIZE + 1], unsigned int *, unsigned int);

void lab_6(void)
{
	//For input data.
	char data[2000][BUF_SIZE + 1] = {'\0'};
	//For name count.
	unsigned int count[2000] = {0};
	//For loop variable.
	unsigned int i, length;

	scanf("%u", &length);
	getchar();

	//Inputing data.
	for(i = 0; i < length; ++i)
	{
		scanf("%"XSTR(BUF_SIZE)"[^ ]%*[^\n]", data[i]);
		getchar();
	}
	name_sort(data, length);
	unsigned int count_length = name_count(data, count, length);
	name_print(data, count, count_length);
	
	/*test data:
3
Spain Donna Elvira
England Jane Doe
Spain Donna Anna
	*/
}

void name_sort(char (*data)[BUF_SIZE + 1], unsigned int length)
{
	unsigned int i, j;

	//Taking bubble sort for each string.
	for(i = 0; i < length - 1; ++i)
	{
		for(j = 0; j < length - 1; ++j)
		{
			if(strcmp(data[i], data[i + 1]) > 0)
				name_swap(data[i], data[i + 1]);
		}
	}
}

//Just swaping the string.
static inline void name_swap(char *X, char *Y)
{
	static char temp[BUF_SIZE + 1] = {'\0'};
	static unsigned int i = 0;

	for(i = 0; i < BUF_SIZE; ++i)
	{
		temp[i] = X[i];
		X[i] 	= Y[i];
		Y[i] 	= temp[i];
	}
}

//Counting the identical string to unsigned int array *count* .
unsigned int name_count(char (*data)[BUF_SIZE + 1], unsigned int *count, unsigned int length)
{
	unsigned int i = 0, j = 0, offset = 1;

	while(i < length)
	{
		if(strcmp(data[i], data[i + offset]) == 0)
		{
			count[j] += 1;
			offset 	 += 1;
		}
		else
		{
			i 		 += 1;
			j 		 += 1;
			offset 	  = 1;
		}
	}
	return j;
}

void name_print(char (*result)[BUF_SIZE + 1], unsigned int *count, unsigned int length)
{
	unsigned int i = 0, j = 0;

	//Using two pointer.
	while(i < length)
	{
		printf("%s %d\n", result[i], count[j] + 1);
		i += count[j] + 1;
		j += 1;
	}
}

#undef BUF_SIZE
#undef STR
#undef XSTR