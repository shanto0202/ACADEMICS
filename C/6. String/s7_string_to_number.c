#include <stdio.h>
#include <stdlib.h>
int main()
{
    char str[20] = "1023";
    int num = atoi(str);
    long l = atol(str);
    float f = atof("12.35");
    printf("%d %ld %f", num, l, f);
    return 0;
}