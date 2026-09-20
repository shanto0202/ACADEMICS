#include <stdio.h>
int main()
{
    int a[5] = {1, 3, 4, 5, 8};
    int *p = a;               // int *p = &a[0] access the first element of the array
    printf("%d\n", *p);       // 1
    printf("%d\n", *p + 1);   // 2
    printf("%d\n", *(p + 2)); // 4
    printf("%d\n", p);
    printf("%d\n", p + 3);
    return 0;
}