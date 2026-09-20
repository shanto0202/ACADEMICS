#include <stdio.h>
int main(int argc, char *argv[])
{
    /*
    need to run this program form the terminal like:
    gcc command_line_argument.c -o output
    .\output 5 6 2 //(random numbers)
    */
    printf("Number of arguments: %d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    return 0;
}