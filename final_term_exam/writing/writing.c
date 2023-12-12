#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define problem_4 0



#ifdef problem_1

int main(void)
{
	unsigned int a, c;
	double angle, b;
	
	while(1)
	{
		scanf("%u%u%lf", &a, &c, &angle);
		getchar();
		
		if(angle <= 0 || angle >= 180)
			goto DEBUG;
		
		angle = angle * 3.1415926 / 180;
		b = a*a + c*c - 2*a*c*cos(angle);
		
		if(b <= 0)
			goto DEBUG;
		
		b = pow(b, 0.5);

		printf("%.2lf\n", b);
		continue;
DEBUG:
		printf("Invalid\n");
		continue;
	}

	return 0;
}

#endif



#ifdef problem_2

#define TERM_LENGTH 30
#define LIST_SIZE   100

typedef union list_s
{
	struct
	{
		char product[TERM_LENGTH];
		unsigned int price;
	};
	struct
	{
		char item[TERM_LENGTH];
		unsigned int amount;
	};
} list_t;

unsigned int find_price(list_t *, char *);
unsigned long long int order_summation(list_t *, list_t *, unsigned int);

int main(void)
{
	FILE *menu_ptr   = fopen("menu.txt",   "r"),
		 *order_ptr  = fopen("order.txt",  "r"),
		 *result_ptr = fopen("result.txt", "w");
	
	list_t menu [LIST_SIZE] = {0}, 
		   order[LIST_SIZE] = {0};
	
	register unsigned int size;
	register char token;
	
	size = 0;
	while(fscanf(menu_ptr, "%s%u", menu[size].product, &menu[size].price) == 2)
	{
		++size;
	}
	
	size = 0;
	while(fscanf(order_ptr, "%s%u", order[size].item, &order[size].amount) == 2)
	{
		++size;
		fgetc(order_ptr);
		token = fgetc(order_ptr);
		
		if(token == '#')
		{
			fprintf(result_ptr, "%llu\n", order_summation(menu, order, size));
			size = 0;
			continue;
		}
		ungetc(token, order_ptr);
	}
	
	return 0;
}

unsigned int find_price(list_t *menu, char *item)
{
	register unsigned int each;
	
	each = 0;
	while(1)
	{
		if(!strcmp(item, menu[each].product))
		{
			return menu[each].price;
		}
		
		++each;
	}
}

unsigned long long int order_summation(list_t *menu, list_t *order, unsigned int size)
{
	register unsigned int each, summation;
	
	for(summation = each = 0; each < size; ++each)
	{
		summation += find_price(menu, order[each].item) * order[each].amount;
	}
	
	return summation;
}

#endif



#ifdef problem_3

#define ARRAY_LENGTH 100
#define SWAP(x, y) 		\
		temp = (x);		\
		(x)  = (y);		\
		(y)  = temp;

void sort (double [], unsigned int);
void merge(double [], unsigned int,
		   double [], unsigned int,
		   double []);

int main(void)
{
	FILE *file1  = fopen("file1.txt",  "r"), 
		 *file2  = fopen("file2.txt",  "r"), 
		 *result = fopen("result.txt", "w");
	
	double array1[ARRAY_LENGTH] = {0},
		   array2[ARRAY_LENGTH] = {0},
		   array [ARRAY_LENGTH] = {0};
	
	register unsigned int size1, size2, size, each;
	register char token;
	
	size = size1 = size2 = 0;
	
	while(1)
	{
		fscanf(file1, "%lf", &array1[size1++]);
		token = fgetc(file1);
		
		if(token != ' ')
		{
			break;
		}
	}
	//for(each = 0; each < size1; ++each)	printf("%lf ", array1[each]);
	while(1)
	{
		fscanf(file2, "%lf", &array2[size2++]);
		token = fgetc(file2);
		
		if(token != ' ')
		{
			break;
		}
	}
	
	size = size1 + size2;
	sort (array1, size1);
	sort (array2, size2);
	merge(array1, size1, array2, size2, array);
	
	for(each = 0; each < size; ++each)
	{
		if(array[each] == array[each + 1])
		{
			continue;
		}
		
		fprintf(result, "%.1lf ", array[each]);
		printf("%.1lf ", array[each]);
	}
	
	return 0;
}

void sort(double array[], unsigned int size)
{
	register double temp;
	register unsigned int i, j;
	
	size -= 1;
	
	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < size; ++j)
		{
			if(array[j] > array[j + 1])
			{
				SWAP(array[j], array[j + 1]);
			}
		}
	}
}

void merge(double array1[], unsigned int size1,
		   double array2[], unsigned int size2,
		   double array [])
{
	register unsigned int each1, each2, index;
	
	index = each1 = each2 = 0;
	
	while(each1 < size1 && each2 < size2)
	{
		if(array1[each1] < array2[each2])
		{
			array[index++] = array1[each1++];
		}
		else
		{
			array[index++] = array2[each2++];
		}
	}
	while(each1 < size1)
	{
		array[index++] = array1[each1++];
	}
	while(each2 < size2)
	{
		array[index++] = array2[each2++];
	}
}

#endif



#ifdef problem_4

#define NAME_LENGTH 20

typedef struct node_s
{
	char name[NAME_LENGTH];
	struct node_s *left;
	struct node_s *right;
} node_t;

void add_node(node_t *);
void traverse(node_t *);
node_t *find_node(node_t *, char *);

int main(void)
{
	unsigned int count, flag = 1;
	char str[NAME_LENGTH] = {'\0'};
	node_t *root = (node_t *)malloc(sizeof(node_t));
	root->left = NULL;
	root->right = NULL;

	scanf("%u", &count);
	getchar();
	
	while(count--)
	{
		scanf("%s", str);
		getchar();

		if(flag)
		{
			strcpy(root->name, str);
			flag = 0;
		}
		printf("|%p %s|\n", find_node(root, str), find_node(root, str)->name);
		add_node(find_node(root, str));
	}

	traverse(root);
}

void add_node(node_t *node)
{
	node_t *temp = (node_t *)malloc(sizeof(node_t));
	temp->left = NULL;
	temp->right = NULL;
	scanf("%s", temp->name);
	getchar();

	if(node->left == NULL)
	{
		node->left = temp;
		//printf("|node->left %s\n", node->left->name);
		return;
	}
	if(node->right == NULL)
	{
		node->right = temp;
		//printf("node->right %s|\n", node->right->name);
		return;
	}
	printf("Wrong input!\n");
	return;
}

node_t *find_node(node_t *node, char *str)
{
	if(node == NULL) return NULL;
	//printf("|%s %s %d|\n", node->name, str, !strcmp(node->name, str));
	find_node(node->left, str);
	if(!strcmp(node->name, str)) return node;
	find_node(node->right, str);
}

void traverse(node_t *node)
{
	if(node == NULL) return;

	traverse(node->left);
	printf("%s\n", node->name);
	traverse(node->right);
}

/*
Input:
8
Mary Bob
Mary Susan
Bob Tom
Bob Ken
Tom Lucy
Ken Vivian
Susan John
John James

Bob James
Bob John
Bob Tom
*/

#endif