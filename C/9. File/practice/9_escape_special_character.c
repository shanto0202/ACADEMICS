#include <stdio.h>
int main()
{
    FILE *in = fopen("myfile.txt", "r");
    FILE *out = fopen("output.txt", "w");
    if (in == NULL || out == NULL)
    {
        fprintf(stderr, "Error: Cannot open\n");
        return 1;
    }
    char c;
    while ((c = fgetc(in)) != EOF)
    {
        if (c == '\t')
            fputs("\\t", out);
        else if (c == '\n')
            fputs("\\n", out);
        else
            fputc(c, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}