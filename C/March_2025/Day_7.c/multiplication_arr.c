#include <stdio.h>
int main()
{
    int r1, r2, c2, c1;
    printf("Enter row and column of first matrices: ");
    scanf("%d %d", &r1, &c1);

    int arr_1[r1][c1];
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++)
        {
            scanf("%d", &arr_1[i][j]);
        }
    }
    printf("Enter row and column of second matrices: ");
    scanf("%d %d", &r2, &c2);

    int arr_2[r2][c2];
    for (int i = 0; i < r2; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            scanf("%d", &arr_2[i][j]);
        }
    }
    int arr_3[r1][c2];
    if (c1 != r2)
    {
        printf("multiplication not possible");
        // exit(356);
    }
    else
    {
        for (int i = 0; i < r1; i++)
        {
            for (int j = 0; j < c2; j++)
            {
                int sum = 0;
                for (int k = 0; k < c1; k++)
                {
                    sum = sum + arr_1[i][k]*arr_2[k][j];
                }
                arr_3[i][j]=sum;
            }
        
        }
    }
    for(int i = 0; i < r1; i++)
    {
        for(int j = 0; j< c2; j++)
        {
            printf("%d ",arr_3[i][j]);
        }
        printf ("\n");
    }
    return 0;
}