#include <stdio.h>
#include <string.h>

void reverse_str(char *str)
{
    int n = strlen(str);
    for (int i = 0; i <= (n / 2 - 1); i++)
    {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}