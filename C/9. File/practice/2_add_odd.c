#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Parameter: %s <filename>\n", argv[0]);
        return 1;
    }
    int s = 0, num;
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR");
        return 1;
    }
    while (fscanf(fp, "%d", &num) == 1) // Read complete numbers
    {
        if (num % 2 != 0)
        {
            s = s + num;
        }
    }
    printf("%d", s);
    fclose(fp);
    return 0;
}