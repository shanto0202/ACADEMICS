#include <stdio.h>
int main()
{
    FILE *fp = fopen("myfile.txt", "w+");
    if (!fp)
    {
        perror("Error opening file");
        return 1;
    }
    // Write alphabet to file
    for (char c = 'A'; c <= 'Z'; c++)
    {
        fputc(c, fp);
        //fprintf(fp,"\n");
    }
    // Read 5th character using SEEK_SET
    fseek(fp, 4, SEEK_SET);
    printf("5th character: %c\n", fgetc(fp)); // Should print 'E'
    // Move 5 positions forward from current
    fseek(fp, 5, SEEK_CUR);
    printf("10th character: %c\n", fgetc(fp)); // Should print 'J'
    // Move to 5 bytes before end
    fseek(fp, -5, SEEK_END);
    printf("5th from last: %c\n", fgetc(fp)); // Should print 'V'
    fclose(fp);
    return 0;
}