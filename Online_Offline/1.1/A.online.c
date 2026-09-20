#include <stdio.h>
#include <stdlib.h>

void rotateMatrix(int **matrix, int N)
{
    // Allocate memory for the rotated matrix
    int **rotated = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        *(rotated + i) = (int *)malloc(N * sizeof(int));
    }

    // Perform rotation
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            *(*(rotated + j) + (N - 1 - i)) = *(*(matrix + i) + j);
        }
    }

    // Copy rotated matrix back to the original matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            *(*(matrix + i) + j) = *(*(rotated + i) + j);
        }
    }

    // Free the rotated matrix
    for (int i = 0; i < N; i++)
    {
        free(*(rotated + i));
    }
    free(rotated);
}

int main()
{
    int N;
    scanf("%d", &N);

    // Allocate memory for the matrix
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        *(matrix + i) = (int *)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++)
        {
            scanf("%d", *(matrix + i) + j);
        }
    }

    // Rotate the matrix
    rotateMatrix(matrix, N);

    // Print the rotated matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < N; i++)
    {
        free(*(matrix + i));
    }
    free(matrix);

    return 0;
}