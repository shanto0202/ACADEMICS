#include <stdio.h>
void hexToOctal(char *hex)
{
    int num;
    sscanf(hex, "%x", &num); // hex to decimal
    printf("%o\n", num);     // Directly print as octal
}
int main()
{
    char *p = "A7B8";
    hexToOctal(p);
    return 0;
}
