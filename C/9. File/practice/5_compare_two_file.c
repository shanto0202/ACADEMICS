#include <stdio.h>
#include <string.h>
int main()
{
    FILE *f1 = fopen("myfile.txt", "r");
    FILE *f2 = fopen("output.txt", "r");
    char line1[200], line2[200];
    int lineNum = 1;
    while (fgets(line1, 200, f1) && fgets(line2, 200, f2))
    {
        if (strcmp(line1, line2))
        {
            printf("Mismatch at line %d:\nFile1: %s\nFile2: %s", lineNum, line1, line2);
            break;
        }
        lineNum++;
    }
    fclose(f1);
    fclose(f2);
    return 0;
}