#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <file1> <file2> <output_file>\n", argv[0]);
        return 1;
    }
    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "r");
    FILE *out = fopen(argv[3], "w");
    if (f1 == NULL)
    {
        fprintf(stderr, "ERROR: Cannot open file '%s'\n", argv[1]);
        return 1;
    }
    if (f2 == NULL)
    {
        fprintf(stderr, "ERROR: Cannot open file '%s'\n", argv[2]);
        fclose(f1);
        return 1;
    }
    if (out == NULL)
    {
        fprintf(stderr, "ERROR: Cannot create output file '%s'\n", argv[3]);
        fclose(f1);
        fclose(f2);
        return 1;
    }
    char buffer[1024]; // Larger buffer for better performance
    while (fgets(buffer, sizeof(buffer), f1) != NULL)
    {
        //fputs(buffer, out);
        fprintf(out,"%s",buffer);
    }
    while (fgets(buffer, sizeof(buffer), f2) != NULL)
    {
        //fputs(buffer, out);
        fprintf(out,"%s",buffer);
    }
    fclose(f1);
    fclose(f2);
    fclose(out);
    printf("Files successfully merged into '%s'\n", argv[3]);
    return 0;
}