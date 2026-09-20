#include <stdio.h>
int strRlen(char s[])
{
    static int i = 0;
    if (s[i] == '\n')
    {
        return 0;
    }
    i++;
    return 1 + strRlen(s);
}
int main()
{
    char s[100];
    fgets(s, sizeof(s), stdin);
    int len = strRlen(s);
    printf("%d", len);
    return 0;
}