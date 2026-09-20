#include <stdio.h>
int main()
{
    int n;
    printf("Enter the size of the matrix : ");
    scanf("%d", &n);
    int matrix[n][n];
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    // Calculate the sum of the first row (reference sum)
    int magicSum = 0;
    for (int j = 0; j < n; j++)
    {
        magicSum += matrix[0][j];
    }
    int isMagic = 1;
    // Check all rows
    for (int i = 0; i < n; i++)
    {
        int rowSum = 0;
        for (int j = 0; j < n; j++)
        {
            rowSum += matrix[i][j];
        }
        if (rowSum != magicSum)
        {
            isMagic = 0;
            break;
        }
    }
    // Check all columns
    if (isMagic)
    {
        for (int j = 0; j < n; j++)
        {
            int colSum = 0;
            for (int i = 0; i < n; i++)
            {
                colSum += matrix[i][j];
            }
            if (colSum != magicSum)
            {
                isMagic = 0;
                break;
            }
        }
    }
    // Check main diagonal (only if still magic)
    if (isMagic)
    {
        int diagSum = 0;
        for (int i = 0; i < n; i++)
        {
            diagSum += matrix[i][i];
        }
        if (diagSum != magicSum)
        {
            isMagic = 0;
        }
    }
    // Check anti-diagonal (only if still magic)
    if (isMagic)
    {
        int antiDiagSum = 0;
        for (int i = 0; i < n; i++)
        {
            antiDiagSum += matrix[i][n - 1 - i];
        }
        if (antiDiagSum != magicSum)
        {
            isMagic = 0;
        }
    }
    if (isMagic)
    {
        printf("MAGIC SQUARE\n");
    }
    else
    {
        printf("NOT A MAGIC SQUARE\n");
    }
    return 0;
}