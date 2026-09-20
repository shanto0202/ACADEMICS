#include <stdio.h>
#include <string.h>
int main()
{
    char s[] = "this , is - bangladesh"; // Character array (MODIFIABLE)
    char *p = strtok(s, " ,-");
    while (p != NULL)
    {
        printf("%s\n", p);
        p = strtok(NULL, " ,-"); // Subsequent calls with NULL
    }
    return 0;
}