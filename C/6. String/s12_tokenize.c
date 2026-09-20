#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *strtoks(char *str, char c)
{
    static char *gstr;
    char token[100];
    char *ptoken;
    if (str != NULL)
    {
        gstr = str;
    }
    if (*gstr == '\0')
        return NULL;
    int i = 0;
    while (*gstr != c && *gstr != '\0')
    {
        token[i] = *gstr;
        gstr++;
        i++;
    }
    token[i] = '\0';
    if (*gstr == c)
        gstr++;
    if (i > 0)
    {
        ptoken = malloc(strlen(token) + 1);
        strcpy(ptoken, token);
        return ptoken;
    }
    return NULL;
}
int main()
{
    char *str = "You.live.in.Dhaka.Right.";
    char *tokens;
    int j = 0;
    do
    {
        if (j == 0)
            tokens = strtoks(str, '.');
        else
            tokens = strtoks(NULL, '.');
        if (tokens != NULL)
            printf("%s\n", tokens);
        j++;
    } while (tokens != NULL);
    return 0;
}