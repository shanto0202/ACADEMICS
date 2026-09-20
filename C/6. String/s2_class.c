#include <stdio.h>
int main()
{
    char ccountry[] = "China";
    char *bcountry = "Bangladesh";
    char *acountry = "Australia";
    bcountry = acountry;
    printf("%s\n", bcountry);
    bcountry = ccountry;
    printf("%s\n", bcountry);
    char *s = "I Love you";
    printf("%s", s);
    return 0;
}