#include <stdio.h>
int main()
{
    // Open input file for reading
    FILE *ifp = fopen("myfile.txt", "r");
    if (ifp == NULL)
    {
        fprintf(stderr, "Input file could not be opened\n"); //standard error
        return 1;
    }
    // Open output file for writing
    FILE *ofp = fopen("output.txt", "w");
    if (ofp == NULL)
    {
        fprintf(stderr, "Output file could not be opened\n");
        fclose(ifp); // Close input file before exiting
        return 1;
    }
    // Copy contents character by character
    while (1)
    {
        char mychar = fgetc(ifp); // Read a character
        if (mychar == EOF)
        {
            break; // End of file
        }
        fputc(mychar, ofp); // Write character to output
    }
    fclose(ifp);
    fclose(ofp);
    printf("File copied successfully.\n");
    return 0;
}
