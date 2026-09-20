#include <stdio.h>
void TOH(int n, char s, char b, char t)
{
    if (n == 1)
    {
        printf("Move disc 1 from %c to %c\n", s, t);
    }
    else
    {
        // Step 1: Move n-1 discs from source to temporary
        TOH(n - 1, s, t, b);
        // Step 2: Move nth disc from source to target
        printf("Move disc %d from %c to %c\n", n, s, t);
        // Step 3: Move n-1 discs from temporary to target
        TOH(n - 1, b, s, t);
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    TOH(n, 'A', 'B', 'C'); // A = source, B = temporary, C = target
    return 0;
}