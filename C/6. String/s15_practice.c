#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *reverse(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++)
    {
        char temp = *(str + i);
        *(str + i) = *(str + n - i - 1);
        *(str + n - i - 1) = temp;
    }
    return str;
}
int main()
{
    char *str = (char *)malloc(100 * sizeof(char));
    scanf("%s", str);
    str = reverse(str);
    fputs(str, stdout);
    return 0;
}