#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    char *a = malloc(100 * sizeof(char));
    char *b = malloc(100 * sizeof(char));
    fgets(a, 100, stdin);
    fgets(b, 100, stdin);
    char *p = strtok(a, b);
    while (p != NULL)
    {
        printf("%s ", p);
        p = strtok(NULL, b);
    }
    free(a);
    free(b);
    return 0;
}