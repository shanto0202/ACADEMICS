#include <stdio.h>
int main()
{
    int a, b;
    int *p, *q;
    p = &a;
    q = &b;
    scanf("%d", &a); //*p=a;
    scanf("%d", q);  // p=&a
    printf("number: %d & memory allocation: %d\n", *p, p);
    printf("number: %d & memory allocation: %d\n", *q, q);
    int r = *p * *q;
    printf("%d\n", r);
    
    int *h;
    h = p;
    printf("%d\n", *h);

    printf("%d\n",h);
    h++;
    printf("%d\n",h); //if char, float or double, it will increase by 1
    return 0;
}