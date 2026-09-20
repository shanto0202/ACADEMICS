#include <stdio.h>
int main()
{
    FILE *fp;
    fp = fopen("myfile.txt", "a");
    if (fp == NULL)
    {
        printf("ERROR");
        return 0;
    }
    char s[100];
    fgets(s, sizeof(s), stdin);
    fprintf(fp, "%s", s);
    fclose(fp);
    return 0;
}