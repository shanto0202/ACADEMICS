#include <stdio.h>
int main()
{
    FILE *fp;
    fp = fopen("myfile.txt", "r");
    if (fp == NULL)
    {
        printf("ERROR");
        fclose(fp);
    }
    int a;
    float f;
    char c[10];
    fscanf(fp, "%d %f %s", &a, &f, c);
    printf("%d %f %s", a, f, c);
    fclose(fp);
    return 0;
}