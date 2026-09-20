#include <stdio.h>
int main()
{
    int n, m, i, j, max;
    printf("Row Column: ");
    scanf("%d %d", &n, &m);
    int arr[n][m], arr1[n], arr2[m];
    for (i = 0; i < n; i++)
    {
        arr1[i] = 0;
        for (j = 0; j < m; j++)
        {
            scanf("%d", &arr[i][j]);
            arr1[i] = arr1[i] + arr[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("Student %d: %d\n", i + 1, arr1[i]);
    }
    for (i = 0; i < m; i++)
    {
        max = -1;
        for (j = 0; j < n; j++)
        {
            if (max < arr[j][i])
            {
                max = arr[j][i];
            }
        }
        arr2[i] = max;
    }
    for (i = 0; i < m; i++)
    {
        printf("Subject %d: %d\n", i + 1, arr2[i]);
    }
    return 0;
}