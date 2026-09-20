#include <stdio.h>
int main()
{
    FILE *src = fopen("myfile.txt", "r");
    FILE *dest = fopen("output.txt", "w");
    if (src == NULL || dest == NULL)
    {
        printf("Error opening files");
        return 1;
    }
    char ch;
    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }
    rewind(src); // Move the file pointer back to the beginning of the file.
    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }
    fclose(src);
    fclose(dest);
    return 0;
}