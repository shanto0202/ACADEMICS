#include <stdio.h>
int rev(int n)
{
    int temp, result = 0, reminder;
    temp = n;
    while (temp != 0)
    {
        reminder = temp % 10;
        result = result * 10 + reminder;
        temp = temp / 10;
    }
    return result;
}

int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int p;
    p = rev(n);
    printf("%d", rev(n));
    if (p == n)
    {
        printf("\npalindrom number");
    }
    else
    {
        printf("\nnot a palindrom number");
    }
    return 0;
}