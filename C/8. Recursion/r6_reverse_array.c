#include <stdio.h>
void reverseArray(int a[], int start, int end)
{
    if (start >= end)
        return;
    int temp = a[start];
    a[start] = a[end];
    a[end] = temp;
    reverseArray(a, start + 1, end - 1);
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    reverseArray(arr, 0, n - 1);
    printf("\nReversed array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
