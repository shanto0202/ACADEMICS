#include <stdio.h>
#include <stdlib.h>
int main()
{
    int **p;
    int m, n;
    scanf("%d %d", &m, &n);
    p = malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        *(p + i) = malloc(n * sizeof(int));
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", (*(p + i) + j));
        }
    }
    int min = **p, max = **p;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (*(*(p + i) + j) > max)
                max = *(*(p + i) + j);
            if (*(*(p + i) + j) < min)
                min = *(*(p + i) + j);
        }
    }
    printf("%d %d\n", min, max);
    for (int i = 0; i < m; i++)
    {
        free(*(p + i));
    }
    free(p);
    return 0;
}
