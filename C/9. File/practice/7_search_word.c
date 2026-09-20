#include <stdio.h>
#include <string.h>
int main()
{
    char word[50], line[200];
    printf("Enter word to search: ");
    scanf("%s", word);
    FILE *fp = fopen("myfile.txt", "r");
    while (fgets(line, 200, fp))
    {
        if (strstr(line, word))
        {
            printf("%s", line);
        }
    }
    fclose(fp);
    return 0;
}