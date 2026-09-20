#include <stdio.h>
#include <string.h>
int main()
{
    char *s = "12:30:45";
    char *p = strchr(s, ':');
    if (p)
    {
        printf("%i\n", p - s); // position of the first colon
    }
    char *q = strrchr(s, ':');
    if (p)
    {
        printf("%i", q - s); // position of the last colon
    }
    return 0;
}