#include <stdio.h>
#include <stdlib.h>
void take_input(int ***A, int m, int n)
{
    **A = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        *(*A + i) = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            scanf("%d", *(*A + i) + j);
        }
    }
}
void free_matrix(int **A, int m)
{
    for (int i = 0; i < m; i++)
    {
        free(*(A + i));
    }
    free(A);
}
void print_matrix(int **A, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        printf("\n");
        for (int j = 0; j < n; j++)
        {
            printf("%d ", *(*(A + i) + j));
        }
    }
}
int main()
{
    int m, n;
    printf("Give the Dimension of the matrix: ");
    scanf("%d %d", &m, &n);
    int **A;
    take_input(&A, m, n);
    print_matrix(A, m, n);
    free_matrix(A, m);
}