#include <stdio.h>
#include <stdlib.h>
int main()
{
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    // matrices 3D based array
    int ***arr1;
    arr1 = malloc(x * sizeof(int **));
    for (int i = 0; i < x; i++)
    {
        *(arr1 + i) = malloc(y * sizeof(int *));
        for (int j = 0; j < y; j++)
        {
            *(*(arr1 + i) + j) = malloc(z * sizeof(int));
            for (int k = 0; k < z; k++)
            {
                printf("array2[%d][%d][%d]: ", i, j, k);
                scanf("%d", (*(*(arr1 + i) + j) + k));
            }
        }
    }
    // Free memory
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            free(*(*(arr1 + i) + j));
        }
        free(*(arr1 + i));
    }
    free(arr1);
    // Pointer-based 3D array using single malloc
    int *ptr = (int *)malloc(x * y * z * sizeof(int));
    // Input values using pointer arithmetic
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
            {
                scanf("%d", (ptr + i * (y * z) + j * z + k));
            }
        }
    }
    // Print using pointer arithmetic
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
            {
                printf("%d ", *(ptr + i * (y * z) + j * z + k));
            }
        }
    }
    free(ptr);
    return 0;
}