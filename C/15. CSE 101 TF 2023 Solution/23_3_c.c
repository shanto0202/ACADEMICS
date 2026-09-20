#include <stdio.h>
#include <stdlib.h>
void allocate_mem(int **a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        *(a + i) = (int *)malloc(n * sizeof(int));
    }
}
void scan_num(int **a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", (*(a + i) + j));
        }
    }
}
void addition(int **a, int **b, int m, int n, int **result)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            *(*(result + i) + j) = *(*(a + i) + j) + (*(*(b + i) + j));
        }
    }
}
void subtraction(int **a, int **b, int m, int n, int **result)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            *(*(result + i) + j) = *(*(a + i) + j) - (*(*(b + i) + j));
        }
    }
}
void multiplication(int **a, int **b, int m, int n, int **result)
{
    for (int i = 0; i < m; i++)
    {
        for (int k = 0; k < n; k++)
        {
            int sum = 0;
            for (int j = 0; j < n; j++)
            {
                sum += *(*(a + i) + j) * *(*(b + j) + k); // Fixed indexing
            }
            *(*(result + i) + k) = sum;
        }
    }
}
void free_mem(int **a, int m)
{
    for (int i = 0; i < m; i++)
    {
        free(*(a + i));
    }
    free(a);
}
void print_arr(int **a, int m, int n)
{
    printf("\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", *(*(a + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}
int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int **a = (int **)malloc(m * sizeof(int *));
    allocate_mem(a, m, n);
    int **b = (int **)malloc(m * sizeof(int *));
    allocate_mem(b, m, n);
    int **add = (int **)malloc(m * sizeof(int *));
    int **sub = (int **)malloc(m * sizeof(int *));
    int **mul = (int **)malloc(m * sizeof(int *));
    allocate_mem(add, m, n);
    allocate_mem(sub, m, n);
    allocate_mem(mul, m, n);
    scan_num(a, m, n);
    printf("\nEnter the other matrix of same dimension\n\n");
    scan_num(b, m, n);
    addition(a, b, m, n, add);
    subtraction(a, b, m, n, sub);
    multiplication(a, b, m, n, mul);
    print_arr(add, m, n);
    print_arr(sub, m, n);
    print_arr(mul, m, n);
    // Free all allocated memory
    free_mem(a, m);
    free_mem(b, m);
    free_mem(add, m);
    free_mem(sub, m);
    free_mem(mul, m);
    return 0;
}