#include <stdio.h>

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    int marks[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &marks[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        int total = 0;
        for (int j = 0; j < m; j++)
        {
            total += marks[i][j];
        }
        printf("std #%02d %d\n", i + 1, total);
    }
    for (int i = 0; i < m; i++)
    {
        int highest = marks[0][i];
        for (int j = 0; j < n; j++)
        {
            if (marks[j][i] > highest)
            {
                highest = marks[j][i];
            }
        }
        printf("sub #%02d %d\n", i + 1, highest);
    }
    return 0;
}