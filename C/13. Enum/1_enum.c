#include <stdio.h>
#include <string.h>
enum week
{
    Saturday,
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday
};
int main()
{
    enum week today;
    char str[10];
    scanf("%s", str);
    if (strcmp(str, "Saturday") == 0)
        today = Saturday;
    else if (strcmp(str, "Sunday") == 0)
        today = Sunday;
    else if (strcmp(str, "Monday") == 0)
        today = Monday;
    else if (strcmp(str, "Tuesday") == 0)
        today = Tuesday;
    else if (strcmp(str, "Wednesday") == 0)
        today = Wednesday;
    else if (strcmp(str, "Thursday") == 0)
        today = Thursday;
    else if (strcmp(str, "Friday") == 0)
        today = Friday;
    printf("Day %d", today + 1);
}