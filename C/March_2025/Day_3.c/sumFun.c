#include <stdio.h>
int sum(int a, int b)
{
    int x = a + b;

    return x;
}
int mult(int a, int b)
{
    int mult2=a*b;
    return mult2;
}

int main()
{
    int x, y;
    //  scanf("%d %d",&x,&y);
    int res = mult(2,3);//sum(11, 12);
    printf("%d", res);
    return 0;
}