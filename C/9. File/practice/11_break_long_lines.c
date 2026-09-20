#include <stdio.h>
#include <string.h>
int main()
{
    char line[200];
    FILE *fp = fopen("myfile.txt", "r");
    while (fgets(line, 200, fp))
    {
        if (strlen(line) > 80)
        {
            int pos = 0;
            while (pos < strlen(line))
            {
                int end = (pos + 80 < strlen(line)) ? pos + 80 : strlen(line);
                while (end > pos && line[end] != ' ' && end - pos > 16)
                {
                    end--;
                }
                printf("%.*s\n", end - pos, line + pos);
                pos = end + 1;
            }
        }
        else
        {
            printf("%s", line);
        }
    }
    fclose(fp);
    return 0;
}