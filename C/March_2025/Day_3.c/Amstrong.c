#include <stdio.h>
#include <math.h>
int main()
{
    int n, sum = 0, count = 0, temp, reminder;
    printf("Enter a number: ");
    scanf("%d", &n);    temp = n;
    while (temp != 0)
    {
        count++;
        temp = temp / 10;
    }
    temp = n;
    while (temp != 0)
    {
        reminder = temp % 10;
        sum = sum + pow(reminder, count);
        temp = temp / 10;
    }
    if (sum == n)
    {
        printf("Amstrong Number");
    }
    else
    {
        printf("not amstrong number");
    }
    return 0;
}