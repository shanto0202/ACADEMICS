#include <stdio.h>
int main()
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        static int val = 0; // initialized once in the loop
        val = val + i;
        sum = sum + val;
    }
    printf("%d", sum);
    return 0;
}