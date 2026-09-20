#include <stdio.h>
#include <string.h>
int main()
{
    char t[20] = "Bangla";
    char p[20] = "desh";
    strcat(t, p);
    printf("%s\n", t);
    strcpy(t, "Bangla");
    strncat(t, p, 3);
    printf("%s", t);
    return 0;
}