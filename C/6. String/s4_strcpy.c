#include <stdio.h>
#include <string.h>
int main()
{
    char s[100], t[100], k[100];
    fgets(s, sizeof(s), stdin);
    strcpy(t, s);
    fputs(t, stdout);
    strncpy(k, s+1, 2);
    k[2] = '\0';
    fputs(k, stdout);
    return 0;
}