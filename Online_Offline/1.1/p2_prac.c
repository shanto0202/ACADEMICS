#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *align(char *c, int len, char sep, int mode)
{
    int str_len = strlen(c);
    char *result = (char *)malloc(len + 1);
    // memset(result, 0, len + 1);
    if (mode == 0) // Center alignment
    {
        for (int i = 0; i < (len - str_len) / 2; i++)
        {
            result[i] = sep;
        }
        strcpy(result + (len - str_len) / 2, c);
        for (int i = (len + str_len) / 2; i < len; i++)
        {
            result[i] = sep;
        }
    }
    else if (mode == -1) // Left alignment
    {
        strcpy(result, c);
        for (int i = str_len; i < len; i++)
        {
            result[i] = sep;
        }
    }
    else // Right alignment (mode == 1)
    {
        for (int i = 0; i < len - str_len; i++)
        {
            result[i] = sep;
        }
        strcpy(result + len - str_len, c);
    }
    strcpy(c, result);
    free(result);
    return c;
}
int main()
{
    char c[100], sep;
    int len, mode;
    printf("Enter string: ");
    gets(c);
    printf("Enter length: ");
    scanf("%d", &len);
    printf("Enter separator character: ");
    scanf(" %c", &sep); // Note the space before %c
    printf("Enter mode : ");
    scanf("%d", &mode);
    align(c, len, sep, mode);
    printf("Result: %s", c);
    return 0;
}