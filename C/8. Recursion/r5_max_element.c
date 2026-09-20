#include <stdio.h>
int findMax(int arr[], int index, int n)
{
    if (index == n - 1)
        return arr[index];
    int maxRest = findMax(arr, index + 1, n);
    return (arr[index] > maxRest) ? arr[index] : maxRest;
}
int main()
{
    int arr[] = {5, 12, 7, 3, 18, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum element = %d\n", findMax(arr, 0, n));
    return 0;
}
