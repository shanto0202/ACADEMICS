#include <stdio.h>
#include <stdlib.h>
void removeNegatives(int *input, int n, int **output, int *newsize)
{
    int j = 0;
    *output = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        if (*(input + i) >= 0)
        {
            *(*output + j) = *(input + i);
            j++;
        }
    }
    *newsize = j;
}
int main()
{
    int a, *p, *q, b;
    scanf("%d", &a);
    p = (int *)malloc(a * sizeof(int));
    for (int i = 0; i < a; i++)
    {
        scanf("%d", (p + i));
    }
    removeNegatives(p, a, &q, &b);
    printf("%d\n", b);
    for (int i = 0; i < b; i++)
    {
        printf("%d ", *(q + i));
    }
    free(p);
    free(q);
    return 0;
}