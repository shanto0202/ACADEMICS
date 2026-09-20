#include <stdio.h>
int main()
{
    FILE *fp;
    fp = fopen("myfile.txt", "a+");
    if (fp == NULL)
    {
        printf("ERROR");
        return 0;
    }
    int a = 2;
    float f = 5.2;
    char c = 'p';
    fprintf(fp, "Num: %d\nFloat: %f\nCharacter: %c", a, f, c);
    fclose(fp);
    return 0;
}