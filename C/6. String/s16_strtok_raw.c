#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
char *strtoks(char *str, char *delims)
{
    static char *gstr;
    char token[10];
    char *rtoken;
    // token=(char*)malloc(10);
    if (str != NULL)
    {
        gstr = (char *)malloc(strlen(str) + 1);
        strcpy(gstr, str);
    }
    if (gstr == NULL || strlen(gstr) == 0)
        return NULL;
    // Skip leading delimiters
    while (strchr(delims, *gstr) && *gstr != '\0')
        gstr++;
    if (*gstr == '\0')
        return NULL;
    int i = 0;
    while (!strchr(delims, *gstr) && *gstr != '\0')
    {
        token[i] = *gstr;
        gstr++;
        i++;
    }
    token[i] = 0;
    if (strchr(delims, *gstr))
        gstr++;
    if (strlen(token) > 0)
    {
        rtoken = (char *)malloc(strlen(token) + 1);
        strcpy(rtoken, token);
    }
    else
        return NULL;
    return rtoken;
}
int main()
{
    char *str = (char *)malloc(100);
    fgets(str, 100, stdin);
    str[strcspn(str, "\n")] = '\0';
    char *tokens = (char *)malloc(10);
    char *del = (char *)malloc(4 * sizeof(char));
    fgets(del, 16, stdin);
    int i = 0;
    tokens = strtoks(str, del);
    while (tokens != NULL)
    {
        printf("%s\n", tokens);
        tokens = strtoks(NULL, del);
        i++;
    }
}