#include <stdio.h>
#include <stdlib.h>
int main()
{
    int m, n, q;
    scanf("%d %d %d", &m, &n, &q);
    // Allocate memory for matrix A (m x n)
    int **A = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        *(A + i) = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            scanf("%d", *(A + i) + j);
        }
    }
    // Allocate memory for matrix B (n x q)
    int **B = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        *(B + i) = (int *)malloc(q * sizeof(int));
        for (int j = 0; j < q; j++)
        {
            scanf("%d", *(B + i) + j);
        }
    }
    // Allocate memory for matrix C (m x q)
    int **C = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        *(C + i) = (int *)malloc(q * sizeof(int));
    }
    // Perform matrix multiplication
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            *(*(C + i) + j) = 0;
            for (int k = 0; k < n; k++)
            {
                *(*(C + i) + j) += *(*(A + i) + k) * *(*(B + k) + j);
            }
        }
    }
    // Print matrix C
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < q; j++)
        {
            printf("%d ", *(*(C + i) + j));
        }
        printf("\n");
    }
    // Free allocated memory
    for (int i = 0; i < m; i++)
    {
        free(*(A + i));
    }
    free(A);
    for (int i = 0; i < n; i++)
    {
        free(*(B + i));
    }
    free(B);
    for (int i = 0; i < m; i++)
    {
        free(*(C + i));
    }
    free(C);
    return 0;
}