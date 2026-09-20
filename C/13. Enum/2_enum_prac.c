#include <stdio.h>
#include <string.h>
// macros can cause mismatch!
// #define RED 0
// #define BLUE 1
// #define GREEN 2
enum color
{
    RED,
    BLUE,
    GREEN
}; // 0, 1, 2
enum size
{
    SMALL = 1,
    MEDIUM = 2,
    LARGE = 3
};
int main()
{
    enum color flagMiddle = RED;
    enum color flagAround = GREEN;
    if (flagMiddle != RED)
    {
        printf("incorrect flag middle");
    }
    char const colornames[3][6] = {"red", "blue", "green"};
    char colorname[10];
    enum color colorvalue;
    printf("Enter a color (red, blue, green): ");
    scanf("%s", colorname);
    if (strcmp(colorname, colornames[RED]) == 0)
        colorvalue = RED;
    else if (strcmp(colorname, colornames[BLUE]) == 0)
        colorvalue = BLUE;
    else if (strcmp(colorname, colornames[GREEN]) == 0)
        colorvalue = GREEN;
    printf("You entered: %s\n", colornames[colorvalue]);
    return 0;
}