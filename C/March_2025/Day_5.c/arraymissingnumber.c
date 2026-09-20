#include <stdio.h>
int find_missing(int arr[], int n)
{
    int sum=0;
    for (int i = 0; i < n-1; i++)
    {
        sum=sum+arr[i];
    }

    return (n*(n+1)/2)-sum;
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n-1];
    for (int i = 0; i < n-1; i++)
    {
        scanf("%d", &arr[i]);
    }

printf ("%d", find_missing (arr,n));
    return 0;
}