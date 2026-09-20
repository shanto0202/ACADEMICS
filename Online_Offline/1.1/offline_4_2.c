#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int word_compare(char *a, char *b)
{
    while (*a != '.' && *b != '.')
    {
        if (*a < *b)
            return -1;
        else if (*a > *b)
            return 1;
        a++;
        b++;
    }
    if (*a == '.' && *b == '.')
        return 0;
    else if (*a == '.')
        return -1;
    else
        return 1;
}
int main()
{
    int n;
    scanf("%d", &n);
    char **ptr;
    ptr = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        *(ptr + i) = (char *)malloc(26 * sizeof(char));
        scanf("%s", *(ptr + i));
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (word_compare(*(ptr + j), *(ptr + j + 1)) > 0)
            {
                char *t = *(ptr + j);
                *(ptr + j) = *(ptr + j + 1);
                *(ptr + j + 1) = t;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", *(ptr + i));
    }
    for (int i = 0; i < n; i++)
    {
        free(*(ptr + i));
    }
    free(ptr);
    return 0;
}