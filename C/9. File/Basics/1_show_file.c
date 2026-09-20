#include <stdio.h>
int main()
{
    FILE *fp;
    fp = fopen("myfile.txt", "r");
    char c;
    while (1)
    {
        c = fgetc(fp);
        if (c == EOF)
        {
            break;
        }
        printf("%c", c);
    }
    fclose(fp);
    return 0;
}