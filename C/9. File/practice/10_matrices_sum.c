#include <stdio.h>
int main()
{
    int rows, cols;
    FILE *in = fopen("myfile.txt", "r");
    fscanf(in, "%d %d", &rows, &cols);
    int matrix[rows][cols];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(in, "%d", &matrix[i][j]);
        }
    }
    fclose(in);
    FILE *out = fopen("output.txt", "w");
    fprintf(out, "Row sums (%d rows):\n", rows);
    for (int i = 0; i < rows; i++)
    {
        int sum = 0;
        for (int j = 0; j < cols; j++)
        {
            sum = sum + matrix[i][j];
        }
        fprintf(out, "%d ", sum);
    }
    fprintf(out, "\nColumn sums (%d cols):\n", cols);
    for (int j = 0; j < cols; j++)
    {
        int sum = 0;
        for (int i = 0; i < rows; i++)
        {
            sum = sum + matrix[i][j];
        }
        fprintf(out, "%d ", sum);
    }
    fclose(out);
    return 0;
}