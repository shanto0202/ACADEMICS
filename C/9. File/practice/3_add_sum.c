#include <stdio.h>
int main()
{
    FILE *fp = fopen("myfile.txt", "r+"); // Changed to "r+" for both read and write
    if (fp == NULL)
    {
        printf("Error opening file");
        return 1;
    }
    int num = 0, sum = 0;
    while (fscanf(fp, "%d", &num) == 1)
    {
        sum = sum + num;
    }
    fprintf(fp, "\n%d", sum);
    fclose(fp);
    return 0;
}