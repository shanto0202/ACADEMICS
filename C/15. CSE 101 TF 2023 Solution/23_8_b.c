#include <stdio.h>
int str_len_own(char str[])
{
    if (str[0] == '\0')
    {
        return 0;
    }
    return 1 + str_len_own(++str);
}
int main()
{
    char str[10] = "Sifat";
    printf("%d\n", str_len_own(str));
    return 0;
}