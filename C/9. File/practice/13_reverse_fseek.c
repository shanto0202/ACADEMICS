#include <stdio.h>
int main()
{
    FILE *fp = fopen("myfile.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file");
        return 0;
    }
    // Move to end
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp); // ftell for current position
    // Read backwards
    for (long i = 1; i <= size; i++)
    {
        fseek(fp, -i, SEEK_END);
        putc(fgetc(fp), stdout);
    }
    fclose(fp);
    return 0;
}