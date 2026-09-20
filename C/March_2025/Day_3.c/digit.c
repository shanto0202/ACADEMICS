#include <stdio.h>
int main()
{
    int n, count=0, temp;
    printf("Enter a number: ");    
    scanf("%d", &n);
    temp=n;
    while (temp != 0)
    {
        count++;
        temp=temp/10;
    }
    printf("count %d", count);

    return 0;
}