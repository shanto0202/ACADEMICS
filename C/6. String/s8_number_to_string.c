#include <stdio.h>
int main()
{
    int num = 2354;
    char str[20];
    sprintf(str, "%d", num);
    printf("%s", str);
    return 0;
}