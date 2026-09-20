#include <stdio.h>
#include <ctype.h>
int main()
{
    char s[100];
    fgets(s, sizeof(s), stdin);
    for (int i = 0; i < sizeof(s) - 1; i++)
    {
        s[i] = toupper(s[i]); // ctype.h
    }
    fputs(s, stdout);
    return 0;
}