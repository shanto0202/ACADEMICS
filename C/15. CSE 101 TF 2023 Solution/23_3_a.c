#include <stdio.h>
#include <stdlib.h>
int main()
{
    // let the dimension of the 3d array is l*m*n
    // method 1
    int l, m, n;
    int ***arr = (int ***)(malloc(l * sizeof(int **)));
    for (int i = 0; i < l; i++)
    {
        *(arr + i) = (int **)(malloc(m * sizeof(int *)));
    }
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < m; j++)
        {
            *(*(arr + i) + j) = (int *)(malloc(n * sizeof(int)));
        }
    }
    // method 2
    int *a = (int *)(malloc(m * n * l * sizeof(int)));
}