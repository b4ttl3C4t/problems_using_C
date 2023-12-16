#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define problem_6 0

#ifdef problem_1

int main(void)
{
	unsigned int a, c;
	double angle, b;

	while (1)
	{
		scanf("%u%u%lf", &a, &c, &angle);
		getchar();

		if (angle <= 0 || angle >= 180)
			goto DEBUG;

		angle = angle * 3.1415926 / 180;
		b = a * a + c * c - 2 * a * c * cos(angle);

		if (b <= 0)
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
#define LIST_SIZE 100

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
	FILE *menu_ptr = fopen("menu.txt", "r"),
		 *order_ptr = fopen("order.txt", "r"),
		 *result_ptr = fopen("result.txt", "w");

	list_t menu[LIST_SIZE] = {0},
		   order[LIST_SIZE] = {0};

	register unsigned int size;
	register char token;

	size = 0;
	while (fscanf(menu_ptr, "%s%u", menu[size].product, &menu[size].price) == 2)
	{
		++size;
	}

	size = 0;
	while (fscanf(order_ptr, "%s%u", order[size].item, &order[size].amount) == 2)
	{
		++size;
		fgetc(order_ptr);
		token = fgetc(order_ptr);

		if (token == '#')
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
	while (1)
	{
		if (!strcmp(item, menu[each].product))
		{
			return menu[each].price;
		}

		++each;
	}
}

unsigned long long int order_summation(list_t *menu, list_t *order, unsigned int size)
{
	register unsigned int each, summation;

	for (summation = each = 0; each < size; ++each)
	{
		summation += find_price(menu, order[each].item) * order[each].amount;
	}

	return summation;
}

#endif

#ifdef problem_3

#define ARRAY_LENGTH 100
#define SWAP(x, y) \
	temp = (x);    \
	(x) = (y);     \
	(y) = temp;

void sort(double[], unsigned int);
void merge(double[], unsigned int,
		   double[], unsigned int,
		   double[]);

int main(void)
{
	FILE *file1 = fopen("file1.txt", "r"),
		 *file2 = fopen("file2.txt", "r"),
		 *result = fopen("result.txt", "w");

	double array1[ARRAY_LENGTH] = {0},
		   array2[ARRAY_LENGTH] = {0},
		   array[ARRAY_LENGTH] = {0};

	register unsigned int size1, size2, size, each;
	register char token;

	size = size1 = size2 = 0;

	while (1)
	{
		fscanf(file1, "%lf", &array1[size1++]);
		token = fgetc(file1);

		if (token != ' ')
		{
			break;
		}
	}
	// for(each = 0; each < size1; ++each)	printf("%lf ", array1[each]);
	while (1)
	{
		fscanf(file2, "%lf", &array2[size2++]);
		token = fgetc(file2);

		if (token != ' ')
		{
			break;
		}
	}

	size = size1 + size2;
	sort(array1, size1);
	sort(array2, size2);
	merge(array1, size1, array2, size2, array);

	for (each = 0; each < size; ++each)
	{
		if (array[each] == array[each + 1])
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

	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			if (array[j] > array[j + 1])
			{
				SWAP(array[j], array[j + 1]);
			}
		}
	}
}

void merge(double array1[], unsigned int size1,
		   double array2[], unsigned int size2,
		   double array[])
{
	register unsigned int each1, each2, index;

	index = each1 = each2 = 0;

	while (each1 < size1 && each2 < size2)
	{
		if (array1[each1] < array2[each2])
		{
			array[index++] = array1[each1++];
		}
		else
		{
			array[index++] = array2[each2++];
		}
	}
	while (each1 < size1)
	{
		array[index++] = array1[each1++];
	}
	while (each2 < size2)
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

node_t *temp = NULL;
unsigned int depth;

// void traverse(node_t *);
void add_node(node_t *);
node_t *find_node(node_t *, char *, unsigned int *);
node_t *find_root(node_t *, char *, char *);
unsigned int find_relative(node_t *, char *, char *);

int main(void)
{
	unsigned int count, flag = 1, depth;
	char str[NAME_LENGTH] = {'\0'};
	char another_str[NAME_LENGTH] = {'\0'};
	node_t *root = (node_t *)malloc(sizeof(node_t));
	root->left = NULL;
	root->right = NULL;

	scanf("%u", &count);
	getchar();

	while (count--)
	{
		scanf("%s", str);
		getchar();
		if (flag)
		{
			strcpy(root->name, str);
			flag = 0;
		}
		temp = find_node(root, str, &depth);
		add_node(temp);
	}

	while (1)
	{
		scanf("%s%s", str, another_str);
		printf("%u", find_relative(root, str, another_str));
	}

	return 0;
}

void add_node(node_t *node)
{
	node_t *temp = (node_t *)malloc(sizeof(node_t));
	temp->left = NULL;
	temp->right = NULL;
	scanf("%s", temp->name);
	getchar();

	if (node->left == NULL)
	{
		node->left = temp;
		return;
	}
	if (node->right == NULL)
	{
		node->right = temp;
		return;
	}
	printf("Wrong input!\n");
	return;
}

node_t *find_node(node_t *node, char *str, unsigned int *depth)
{
	if (node == NULL)
		return NULL;

	node_t *result;
	++*depth;

	if ((result = find_node(node->left, str, depth)) != NULL)
		return result;
	if (!strcmp(node->name, str))
		return node;
	if ((result = find_node(node->right, str, depth)) != NULL)
		return result;

	--*depth;
	return NULL;
}

void traverse(node_t *node)
{
	if (node == NULL)
		return;

	traverse(node->left);
	printf("%s\n", node->name);
	traverse(node->right);
}

node_t *find_root(node_t *node, char *str, char *match)
{
	if (node == NULL ||
		!strcmp(node->name, str) ||
		!strcmp(node->name, match))
	{
		return node;
	}

	node_t *left = find_root(node->left, str, match);
	node_t *right = find_root(node->right, str, match);

	if ((left != NULL) && (right != NULL))
	{
		return node;
	}

	if (left != NULL)
	{
		return left;
	}
	else /*right != NULL*/
	{
		return right;
	}
}

unsigned int find_relative(node_t *node, char *str, char *match)
{
	unsigned int depth1, depth2;
	depth1 = depth2 = 0;

	node_t *temp = find_root(node, str, match);
	find_node(temp, str, &depth1);
	find_node(temp, match, &depth2);

	return depth1 + depth2 - 2;
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

#ifdef problem_5

#include <stdio.h>
#include <stdlib.h>
#define SIZE 11

typedef struct
{
	int x;
	int y;
} Point;

Point pt(int, int);
int visit(int[][SIZE], Point, Point);
void scan(int[][SIZE], Point *start, Point *end);
void print(int[][SIZE]);

int main(void)
{
	Point start = {0}, end = {0};
	int maze[SIZE][SIZE] = {0};
	int i, count = 0;

	scanf("%d", &count);
	getchar();

	for (i = 0; i < count; ++i)
	{
		scan(maze, &start, &end);
		visit(maze, start, end);
		if(i != count - 1) maze[end.x][end.y] = 3;
		print(maze);
		start.x = end.x;
		start.y = end.y;
	}
	return 0;
}

Point pt(int x, int y)
{
	Point p = {x, y};
	return p;
}

int visit(int maze[][SIZE], Point start, Point end)
{
	if (maze[start.x][start.y])
		return maze[end.x][end.y];

	maze[start.x][start.y] = 1;
	if (!maze[end.x][end.y] &&
		!visit(maze, pt(start.x + 1, start.y), end) &&
		!visit(maze, pt(start.x, start.y + 1), end) &&
		!visit(maze, pt(start.x - 1, start.y), end) &&
		!visit(maze, pt(start.x, start.y - 1), end))
	{
		maze[start.x][start.y] = 0;
	}
	return maze[end.x][end.y];
}

void scan(int maze[][SIZE], Point *start, Point *end)
{
	int i, j;
	char ch;
	for (i = 0; i < SIZE; ++i)
	{
		for (j = 0; j < SIZE; ++j)
		{
			scanf("%c", &ch);
			switch (ch)
			{
			case 'o':
				maze[i][j] = 0;
				end->x = i;
				end->y = j;
				break;
			case '#':
				maze[i][j] = 2;
				break;
			case '.':
				maze[i][j] = 0;
				break;
			}
			if (j == 0 && maze[i][j] == 0)
			{
				start->x = i;
				start->y = j;
			}
			if (j == SIZE - 1 && maze[i][j] == 0)
			{
				end->x = i;
				end->y = j;
			}
		}
		getchar();
	}
}

void print(int maze[][SIZE])
{
	int i, j;
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
				printf("o");
			}
		printf("\n");
	}
	printf("\n");
}

/*

2
###########
#.#o......#
#.#######.#
#.........#
#########.#
#.......#.#
#.#.#####.#
#.#.......#
#.#########
..........#
###########
###########
#.....#...#
#####.#.###
#...#.#...#
#.###.###.#
#...#.....#
#.#.###.###
#.#...#.###
#.#.###.###
#.#........
###########

*/

#endif

#ifdef problem_6

#define XSTR(x) STR(x)
#define STR(x) #x

typedef struct time_table_s
{
	int hours;
	int minute;
	int second;
} time_table_t;

void scan(time_table_t *);
void add(time_table_t *, time_table_t *, char *);
void calibrate(time_table_t *, char *);

int main(void)
{
	time_table_t table = {0};
	time_table_t bias = {0};

	char time_table[10] = {0};
	char bias_operator[10] = {0};
	char ch;

	while (1)
	{
		scan(&table);
		scanf("%s", time_table);
		getchar();

		while (1)
		{
			if ((ch = getchar()) == '#')
				break;
			ungetc(ch, stdin);

			scanf("%s", bias_operator);
			getchar();
			scan(&bias);

			add(&table, &bias, bias_operator);
			calibrate(&table, time_table);
		}

		printf("%dh%dm%ds %s\n", table.hours, table.minute, table.second, time_table);
	}

	return 0;
}

void scan(time_table_t *table)
{
	int value;
	char unit;

	table->hours = table->minute = table->second = 0;
	while (scanf("%d%c", &value, &unit) == 2)
	{
		switch (unit)
		{
		case 'h':
			table->hours = value;
			break;
		case 'm':
			table->minute = value;
			break;
		case 's':
			table->second = value;
			break;
		}
	}

	// printf("|%dh %dm %ds|\n", table->hours, table->minute, table->second);
}

void add(time_table_t *table, time_table_t *bias, char *bias_operator)
{
	if (!strcmp(bias_operator, "plus"))
	{
		table->hours += bias->hours;
		table->minute += bias->minute;
		table->second += bias->second;
	}
	else
	{
		table->hours -= bias->hours;
		table->minute -= bias->minute;
		table->second -= bias->second;
	}
}

void calibrate(time_table_t *table, char *time)
{
	if (table->second > 60)
	{
		table->second -= 60;
		++table->minute;
	}
	else if (table->second < 0)
	{
		table->second += 60;
		--table->minute;
	}

	if (table->minute > 60)
	{
		table->minute -= 60;
		++table->hours;
	}
	else if (table->minute < 0)
	{
		table->second += 60;
		--table->hours;
	}

	if (table->hours > 12)
	{
		table->hours -= 12;
		goto EXCHANGE;
	}
	else if (table->hours < 0)
	{
		table->hours += 12;
		goto EXCHANGE;
	}
	return;

EXCHANGE:
	if (!strcmp(time, "p.m."))
	{
		strcpy(time, "a.m.");
	}
	else
	{
		strcpy(time, "p.m.");
	}
}

/*
10h13m7s p.m.
plus 4h2m
minus 3m2s
#
5h10m7s a.m.
plus 3h8m3s
plus 2h
minus 3m
minus 10s
#

*/

#endif
