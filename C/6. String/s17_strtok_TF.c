#include <stdio.h>
#include <string.h>
#include <stdio.h>
char *my_strtok(char *str, char *delim)
{
    static char *current; // remembers position between calls
    if (str != NULL)
        current = str;
    if (current == NULL)
        return NULL;
    // Skip leading delimiters
    while (*current && strchr(delim, *current))
        current++;
    if (*current == '\0')
        return NULL;
    char *token_start = current;
    // Move until next delimiter or end of string
    while (*current && !strchr(delim, *current))
        current++;
    if (*current)
    {
        *current = '\0';
        current++;
    }
    else
    {
        current = NULL;
    }
    return token_start;
}
int main()
{
    char str[] = "Hello,world;test:string";
    char *token = my_strtok(str, ",;:");
    while (token != NULL)
    {
        printf("%s\n", token);
        token = my_strtok(NULL, ",;:");
    }
    return 0;
}