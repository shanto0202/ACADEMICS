#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    scanf("%s", str);
    int multiplier = 1;
    int n = strlen(str);
    int decimal = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int temp = 0;
        if (str[i] >= '0' && str[i] <= '9')
        {
            decimal += multiplier * (str[i] - '0');
        }
        else
        {
            decimal += multiplier * (str[i] - 'A' + 10);
        }
        multiplier *= 16;
    }
    char octal[100];
    int c = 0;
    do
    {
        octal[c] = '0' + (decimal % 8);
        decimal /= 8;
        c++;
    } while (decimal);
    octal[c] = '\0';
    for (int i = 0; i <= (c / 2 - 1); i++)
    {
        char temp = octal[i];
        octal[i] = octal[c - 1 - i];
        octal[c - 1 - i] = temp;
    }
    printf("%s\n", octal);
    return 0;
}