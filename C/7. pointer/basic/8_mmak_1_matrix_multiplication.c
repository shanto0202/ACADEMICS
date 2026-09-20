#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int **take_input(int m, int n)
{
    int **a;
    a = (int **)malloc(m * sizeof(int *));
    assert(a != NULL);
    for (int i = 0; i < m; i++)
    {
        a[i] = (int *)malloc(n * sizeof(int));
        assert(a[i] != NULL);
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    return a;
}
void print(int **a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
int **multiply(int m, int k, int n, int **a, int **b)
{
    int **c;
    c = (int **)malloc(m * sizeof(int *));
    assert(c != NULL);
    for (int i = 0; i < m; i++)
    {
        c[i] = (int *)malloc(n * sizeof(int));
        assert(c[i] != NULL);
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int sum = 0;
            for (int l = 0; l < k; l++)
            {
                sum += a[i][l] * b[l][j];
            }
            c[i][j] = sum;
        }
    }
    return c;
}
void freearray(int m, int **a)
{
    for (int i = 0; i < m; i++)
    {
        if (a[i] != NULL)
            free(a[i]);
    }
    if (a != NULL)
        free(a);
}
int main()
{
    int a1, b1, c1, d1;
    printf("First Matrix Row Column: ");
    scanf("%d %d", &a1, &b1);
    printf("Second Matrix Row Column: ");
    scanf("%d %d", &c1, &d1);
    int **a = take_input(a1, b1);
    int **b = take_input(c1, d1);
    int **c = multiply(a1, b1, d1, a, b);
    print(c, a1, d1);
    freearray(a1, a);
    freearray(b1, b);
    freearray(a1, c);
}
