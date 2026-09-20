#include <stdio.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Parameter: %s <filename>\n", argv[0]);
        return 1;
    }
    char line[1000];
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR");
        return 1;
    }
    printf("Character by Character:\n");
    char ch;
    int char_count = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        char_count++;
        printf("character %d: %c\n", char_count, ch);
    }
    //fseek(fp, 0, SEEK_SET);  // Same as rewind(fp)
    rewind(fp);
    printf("String by string:\n");
    char s[100];
    int string_count = 0;
    while (fscanf(fp, "%s", s) == 1)
    {
        string_count++;
        printf("string %d: %s\n", string_count, s);
    }

    rewind(fp);
    printf("Line by Line:\n");
    int line_number = 1;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("Line %d: %s", line_number, line);
        line_number++;
    }
    fclose(fp);
    return 0;
}