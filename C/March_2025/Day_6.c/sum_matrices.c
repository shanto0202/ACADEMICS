#include <stdio.h>
int main()
{
    int r, c;
    printf("Enter row and column: ");
    scanf("%d %d", &r, &c);
    int mat_1[r][c], mat_2[r][c], mat_3[r][c];
    printf("Enter the value for mat_1: \n");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            scanf("%d", &mat_1[i][j]);
        }
    }

    printf("Enter the value for mat_2: \n");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            scanf("%d", &mat_2[i][j]);
        }
    }
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            mat_3[i][j] = mat_1[i][j] - mat_2[i][j];
        }
    }
    printf("sum: \n");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            // mat_3[i][j]=mat_1[i][j]+mat_2[i][j];
            printf("%d ", mat_3[i][j]);
        }
        printf("\n");
    }

    return 0;
}