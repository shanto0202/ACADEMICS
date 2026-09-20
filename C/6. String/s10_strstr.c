#include <stdio.h>
#include <string.h>
int main()
{
    char text[] = "Hello World";
    char *result = strstr(text, "World");
    printf("Text: %s\n", text);
    printf("Looking for: World\n");
    if (result != NULL)
    {
        printf("Found! Position: %ld\n", result - text);
    }
    else
    {
        printf("Not found!\n");
    }
    char *s = "abcdbc";
    char *t = strstr(s, "bc");
    printf("Original example:\n");
    printf("String: %s\n", s);
    printf("Looking for: bc\n");
    printf("Position: %ld\n", t - s);
    // Example 4: Find all occurrences
    printf("Finding all 'bc' in '%s':\n", s);
    char *ptr = s;
    int count = 1;
    while ((ptr = strstr(ptr, "bc")) != NULL)
    {
        printf("Found #%d at position: %ld\n", count++, ptr - s);
        ptr++; // Move to next character
    }
    return 0;
}