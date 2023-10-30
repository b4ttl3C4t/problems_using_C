#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void ScrollingSign(void);
static void AnEasyProblem(void);
static void MagicFormula(void);
static void SymmetricMatrix(void);
static void ContinuedFractions(void);
static void PrimaryArithmetic(void);
static void AMinimumLandPrice(void);
static void Inception(void);
static void Parity(void);
static void PrimeFrequency(void);
static void SummingDigits(void);
static void HowOldAreYou(void);
static void DivideButNotQuiteConquer(void);
static void SloganLearningOfPrincess(void);
static void Bee(void);
static void TheCountingProblem(void);
static void TheBookThief(void);
static void Sales(void);
static void AlternateTask(void);
static void MutantFlatworldExplorers(void);

//MutantFlatworldExplorers
int main(void)
{
    MutantFlatworldExplorers();
    return 0;
}

static void ScrollingSign(void)
{
    unsigned int n, i, j, k;
    unsigned int left, right, __union__;

    char buf[100][100] = {'\0'};
    
    scanf("%u", &n);
    getchar();

    for(i = 0; i < n; ++i)
    {
        scanf("%u", &left);
        getchar();
        scanf("%u", &right);
        getchar();
        __union__ = 0;

        for(j = 0; j < right; ++j)
        {
            for(k = 0; k < left; ++k)
            {
                scanf("%c", &buf[j][k]);
            }
            getchar();
        }

        __union__ = strlen(buf[0]);
        for(j = 1; j < __union__; ++j)
        {
            if(strncmp(buf[0] + j, buf[1], __union__ - j))
            {
                __union__ = __union__ - j;
                break;
            }
        }

        __union__ = left + (__union__) * (right - 1);
        printf("%u", __union__);

        for(j = 0; j < right; ++j)
        {
            for(k = 0; k < left; ++k)
            {
                buf[j][k] = '\0';
            }
        }
    }
}

static void AnEasyProblem(void)
{
    char ch;
    char table[100] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int  d_table[100] = {0};

    for(int i = 0; i < 100; ++i)
    {
        d_table[i] = i + 1;
    }

    for(int i = 0; i < 3; ++i)
    {
        scanf("%c", &ch);
        getchar();

        for(int j = 0; j < 100; ++j)
        {
            if(table[j] == ch)
            {
                printf("%d\n", d_table[j]);
                break;
            }
        }
    }
}

static void MagicFormula(void)
{
    int a, b, c, d, L;
    unsigned int count, i, result;

    while(1)
    {
        count = 0;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &L);

        if(a == 0 && b == 0 && c == 0 && d == 0 && L == 0 )
        {
            break;
        }

        for(i = 0; i <= L; ++i)
        {
            result = a*i*i + b*i + c;
            if(result % d == 0)
            {
                ++count;
            }
        }
        printf("%u\n", count);
    }
}

static void SymmetricMatrix(void)
{
    int matrix[100][100] = {0};
    unsigned int i, j;
    unsigned int left, right;

    unsigned int number, N;
    scanf("%u", &number);
    getchar();

    while(number--)
    {
        scanf("N = %u", &N);
        getchar();

        for(i = 0; i < N; ++i)
        {
            for(j = 0; j < N; ++j)
            {
                scanf("%u", &matrix[i][j]);
            }
            getchar();
        }

        for(left = 0, right = N - 1; left < right; ++left, --right)
        {
            for(j = 0; j < N; ++j)
            {
                if(matrix[left][j] != matrix[right][N - 1 - j])
                {
                    printf("%s\n", "Non-symmetric");
                    goto BREAK;
                }
            }
        }
        printf("%s\n", "Symmetric");

BREAK:
        for(i = 0; i < N; ++i)
        {
            for(j = 0; j < N; ++j)
            {
                matrix[i][j] = 0;
            }
        }
    }
}

static void ContinuedFractions(void)
{
    unsigned int N, firstFlag;
    unsigned int numerator, denominator, quotient, remainder;
    unsigned int i;

    scanf("%u", &N);
    getchar();
    for(i = 0; i < N; ++i)
    {
        firstFlag = 1;
        scanf("%u%u", &numerator, &denominator);
        
        printf("%c", '[');
        while(1)
        {
            quotient    = numerator / denominator;
            remainder   = numerator % denominator;
            numerator   = denominator;
            denominator = remainder;

            printf("%u", quotient);

            if(remainder == 0)
                break;

            if(firstFlag)
            {
                firstFlag = 0;
                printf("%c", ';');
                continue;
            }
            printf("%c", ',');
        }
        printf("%c", ']');
    }
}

static int char2int(char ch)
{
    return ch - '0';
}

static void PrimaryArithmetic(void)
{
    char op1[10] = {0}, op2[10] = {0};
    unsigned int carry, i, count, flag;

    scanf("%s %s", op1, op2);
    getchar();

    while(op1[0]!='0' || op2[0]!='0')
    {
        for(i = 0, count = 0; i < 10; ++i)
        {
            carry = flag = 0;

            carry += flag;
            if(op1[i] != '\0')
                carry += char2int(op1[i]);
            if(op2[i] != '\0')
                carry += char2int(op2[i]);
            flag = carry >= 10;

            if(flag)
            {
                ++count;
            }
        }

        if(!count)
        {
            printf("No carry operation.\n");
        }
        if(count == 1)
        {
            printf("1 carry operation.\n");
        }
        if(count > 1)
        {
            printf("%u carry operations.\n", count);
        }
        
        scanf("%s %s", op1, op2);
        getchar();
    }
}

static void sort(unsigned int *arr)
{
    static unsigned int i, j, temp;
    
    for(i = 0; i < 40; ++i)
    {
        for(j = 0; j < 39; ++j)
        {
            if(arr[j] > arr[j + 1])
            {
                temp    = arr[j];
                arr[j]  = arr[j+1];
                arr[j+1]= temp;
            }
        }
    }
}

static unsigned long long int my_pow(unsigned int n, unsigned int count)
{
    static long long int i, base;

    for(i = 0, base = n; i < count; ++i)
    {
        n *= base;
    }

    return n;
}

static void AMinimumLandPrice(void)
{
    unsigned int buf[40];
    unsigned int T, i, j, count;
    unsigned int budget;

    scanf("%u", &T);
    getchar();

    for(i = 0; i < T; ++i)
    {
        budget = count = 0;

        for(j = 0; j < 40; ++j)
        {
            buf[j] = 0;
        }

        for(j = 0; j < 40; ++j)
        {
            scanf("%u", &buf[j]);
            getchar();

            if(buf[j] == 0)
            {
                break;
            }
        }
        sort(buf);
        
        for(j = 39; j >= 0; --j)
        {
            if(buf[j] == 0)
            {
                break;
            }
            
            budget += 2 * my_pow(buf[j], count);
            ++count;
        }

        if(budget > 5000000)
        {
            printf("Too expensive\n");
        }
        else
        {
            printf("%u\n", budget);
        }
    }
}

static void Inception(void)
{
    char buf[10000][10] = {0};
    int pointer = 0;
    unsigned int instruction;

    scanf("%u", &instruction);
    getchar();

    for(unsigned int i = 0; i < instruction; ++i)
    {
        scanf("%s", buf[pointer]);
        getchar();

        if(!strcmp(buf[pointer], "Sleep"))
        {
            scanf("%s", buf[pointer]);
            getchar();

            ++pointer;
        }
        else if(!strcmp(buf[pointer], "Test"))
        {
            if(pointer <= 0)
                printf("%s\n", "Not in a dream");
            else
                printf("%s\n", buf[pointer - 1]);
        }
        else if(!strcmp(buf[pointer], "Kick"))
        {
            if(pointer != -1)
                --pointer;
        }
    }
}

static void Parity(void)
{
    unsigned int count, number, parity, i;
    unsigned int buf[20] = {0};

    scanf("%u", &number);
    getchar();

    while(number)
    {
        parity = i = 0;

        printf("The parity of ");
        while(number)
        {
            parity += number & 1;
            buf[i++] = number & 1;
            number >>= 1;
        }
        for(int j = i - 1; j >= 0; --j)
            printf("%u", buf[j]);

        printf(" is %u (mod 2).\n", parity);

        scanf("%u", &number);
        getchar();
    }
}

static int isPrime(int number)
{
    for(int i = 2; i*i <= number; ++i)
    {
        if(number % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

static void PrimeFrequency(void)
{
    unsigned int count[62] = {0};
    char table[62] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    char buf[1000] = {'\0'};
    unsigned int T, length, flag;

    scanf("%u", &T);
    getchar();

    for(int i = 0; i < T; ++i)
    {
        for(int j = 0; j < 62; ++j)
        {
            count[j] = 0;
        }

        scanf("%209[0-9a-zA-Z][^\n]", buf);
        getchar();
        length = strlen(buf);

        for(int j = 0; j < length; ++j)
        {
            for(int k = 0; k < 26; ++k)
            {
                if(buf[j] == table[k])
                {
                    ++count[k];
                    break;
                }
            }
        }
        
        printf("Case %u: ", i + 1);
        flag = 1;
        for(int j = 0; j < 26; ++j)
        {
            if(count[j] > 1 && isPrime(count[j]))
            {
                flag = 0;
                printf("%c", table[j]);
            }
        }
        if(flag)
        {
            printf("empty");
        }
        printf("\n");
    }
}

static void SummingDigits(void)
{
    long long int n, i;
    int buf[10] = {0};

    scanf("%lld", &n);
    getchar();

    while(n)
    {
        for(i = 0; i < 10; ++i)
        {
            buf[i] = 0;
        }

        for(i = 0; i < 10 && n; ++i)
        {
            buf[i] = n % 10;
            n /= 10;
        }

        for(i = 0; i < 10; ++i)
        {
            n += buf[i];
        }

        if(n / 10)
        {
            continue;
        }
        printf("%lld\n", n);

        scanf("%lld", &n);
        getchar();
    }
}

static void HowOldAreYou(void)
{
    int n, sum;
    int D_n, M_n, Y_n;
    int D_o, M_o, Y_o;

    scanf("%d", &n);
    getchar();

    for(int i = 1; i <= n; ++i)
    {
        sum = 0;
        
        scanf("%d/%d/%d", &D_n, &M_n, &Y_n);
        getchar();
        scanf("%d/%d/%d", &D_o, &M_o, &Y_o);
        getchar();

        sum += Y_n - Y_o;
        if(M_o > M_n || (M_o <= M_n && D_o > D_n))
            sum -= 1;

        printf("Case #%d: ", i);
        if(sum < 0)
            printf("Invalid birth date\n");
        else if(sum > 130)
            printf("Check birth date\n");
        else
            printf("%d\n", sum);
    }
}

static void DivideButNotQuiteConquer(void)
{
    long long int number, pair1, pair2, flag, temp;

    scanf("%lld", &number);
    getchar();

    for(int i = 0; i < number; ++i)
    {
        scanf("%lld%lld", &pair1, &pair2);
        getchar();

        for(int j = 0; ;++j)
        {
            temp = pair2;

            for(int k = 0; k < j; ++k)
            {
                temp *= pair2;
            }
            if(temp == pair1)
            {
                flag = 1;
                break;
            }
            if(temp < 0 || pair1 < temp)
            {
                flag = 0;
                break;
            }
        }

        if(flag)
        {
            while(pair1 != 0)
            {
                printf("%lld ", pair1);
                pair1 /= pair2;
            }
        }
        else
        {
            printf("Boring!");
        }
        printf("\n");
    }
}

static inline unsigned int fib(unsigned int n)
{
    static unsigned int i, temp1, temp2, temp3;

    temp1 = temp2 = temp3 = 1;
    for(i = 1; i < n; ++i)
    {
        temp3 = temp2 + temp1;
        temp2 = temp1;
        temp1 = temp3;
    }

    return temp3;
}

static void Bee(void)
{
    unsigned int number, sum1, sum2;

    scanf("%u", &number);
    getchar();

    while(number != -1)
    {
        sum1 = sum2 = 0;
        for(int i = 0; i <= number; ++i)
        {
            sum2 = sum1;
            sum1 += fib(i);
        }
        printf("%u %u\n", sum2, sum1);

        scanf("%u", &number);
        getchar();
    }
}

static void SloganLearningOfPrincess(void)
{
    int N, Q;
    char table[20][2][1000];
    char cmp_str[1000];

    scanf("%d", &N);
    getchar();

    for(int i = 0; i < N; ++i)
    {
        scanf("%999[a-z ][^\n]", table[i][0]);
        getchar();
        scanf("%999[a-z ][^\n]", table[i][1]);
        getchar();
    }

    scanf("%d", &Q);
    getchar();

    for(int i = 0; i < Q; ++i)
    {
        scanf("%999[a-z ][^\n]", cmp_str);
        getchar();

        for(int j = 0; j < N; ++j)
        {
            if(!strcmp(cmp_str, table[j][0]))
            {
                printf("%s\n", table[j][1]);
                break;
            }
        }
    }
}

static void TheCountingProblem(void)
{
    int n, m, i;
    int lower, upper;
    int count[10] = {0};

    scanf("%d%d", &n, &m);
    getchar();

    while(n != 0 || m != 0)
    {
        lower = n;
        upper = m;
        if(lower > upper)
        {
            lower = lower ^ upper;
            upper = lower ^ upper;
            lower = lower ^ upper;
        }

        for(i = lower; i <= upper; ++i)
        {
            m = i;
            while(m)
            {
                ++count[m % 10];
                m /= 10;
            }
        }

        for(i = 0; i < 10; ++i)
        {
            printf("%d ", count[i]);
        }
        printf("\n");

        scanf("%d%d", &n, &m);
        getchar();
        for(i = 0; i < 10; ++i)
        {
            count[i] = 0;
        }
    }
}

static void TheBookThief(void)
{
    int number, sum, i;

    scanf("%d", &number);
    getchar();

    while(number != 0)
    {
        sum = i = 0;
        do
        {
            sum += i;
            ++i;
        }while(sum <= number);
        sum -= number;

        printf("%d %d\n", sum, i-1);

        scanf("%d", &number);
        getchar();
    }
}

static void Sales(void)
{
    int n, m, i, j, k, sum;
    int buf[1000]   = {0};
    int count[1000] = {0};

    scanf("%d", &n);
    getchar();

    for(i = 0; i < n; ++i)
    {
        scanf("%d", &m);
        getchar();

        sum = 0;
        for(j = 0; j < m; ++j)
        {
            scanf("%d", &buf[j]);
            getchar();

            for(k = 0; k < j; ++k)
            {
                if(buf[k] <= buf[j])
                {
                    ++count[j];
                }
            }
            sum += count[j];
        }

        printf("%d\n", sum);

        for(j = 0; j < m; ++j)
        {
            buf[j]   = 0;
            count[j] = 0;
        }
    }
}

static inline int FactorSum(int n)
{
    static int i, sum;

    sum = 0;
    for (i = 1; i <= n; i++)
    {
        if(n % i == 0)
        {
            sum += i;
        }
    }

    return sum;
}

static void AlternateTask(void)
{
    int n, i, sum, count = 0;

    scanf("%d", &n);
    getchar();

    while(n)
    {
        ++count;
        sum = 1;

        if(1 == n)
        {
            printf("Case %d: 1\n", count);
            scanf("%d", &n);
            getchar();
            continue;
        }

        for(i = 1; i < n; ++i)
        {
            if(n == FactorSum(i))
            {
                printf("Case %d: %d\n", count, i);
                break;
            }
        }

        if(i == n)
        {
            printf("Case %d: -1\n", count);
        }

        scanf("%d", &n);
        getchar();
    }
}

static void MutantFlatworldExplorers(void)
{
    int count, i, j;
    
    int n, m;
    int x, y;
    char direct_c;
    int  direct, flag;

    int FlatTable[50][50] = {0};
    char instruction[101] = {'\0'};
    enum direction {up, right, down, left};
    struct forward_t
    {
        int x;
        int y;
    };
    const struct forward_t forward[4] = 
    {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    };

    scanf("%d", &count);
    getchar();

    scanf("%d%d", &n, &m);
    getchar();

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < m; ++j)
        {
            FlatTable[i][j] = 1;
        }
    }

    for(i = 0; i < count; ++i)
    {
        scanf("%d%d%c", &x, &y, &direct_c);
        getchar();

        flag = 0;

        switch (direct_c)
        {
        case 'N':
            direct = up;
            break;
        
        case 'E':
            direct = right;
            break;

        case 'W':
            direct = left;
            break;

        case 'S':
            direct = down;
            break;
        }

        scanf("%s", instruction);
        getchar();
        
        for(j = 0; instruction[j] != '\0'; ++j)
        {
            direct_c = instruction[j];
            
            switch (direct_c)
            {
            case 'L':
                direct = (direct + 3) % 4;
                break;
            
            case 'R':
                direct = (direct + 1) % 4;
                break;

            case 'F':
                x += forward[direct].x;
                y += forward[direct].y;
                if(FlatTable[x][y] == 0)
                {
                    flag = 1;
                }
                break;
            }
        }
        
        switch(direct)
        {
        case up:
            direct_c = 'N';
            break;
        case right:
            direct_c = 'E';
            break;
        case left:
            direct_c = 'W';
            break;
        case down:
            direct_c = 'S';
            break;
        }
        printf("%d %d %c", x, y, direct_c);
        if(flag)
        {
            printf(" LOST\n");
        }
        else
        {
            printf("\n");
        }
    }
}