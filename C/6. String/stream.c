#include <stdio.h>
int main()
{
    int num = 1234;
    char *c = "karim";
    char str[100];
    sprintf(str, "%s %d", c, num);
    printf("%s\n", str);
    int num1;
    char c1[100];
    sscanf(str, "%s %d", c1, &num1);
    printf("Number: %d & Name: %s\n", num1, c1);
    return 0;
}