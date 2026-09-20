#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    // Original array
    char original[] = "Hello";
    printf("=== SHALLOW COPY ===\n");
    // Shallow copy - just copying the pointer
    char *shallow = original; // Points to same memory
    printf("Original: %s\n", original);
    printf("Shallow:  %s\n", shallow);
    // Modify through shallow copy
    shallow[0] = 'X';
    printf("After changing shallow[0] to 'X':\n");
    printf("Original: %s\n", original); // Also changed!
    printf("Shallow:  %s\n", shallow);
    printf("\n=== DEEP COPY ===\n");
    // Reset original
    strcpy(original, "Hello");
    // Deep copy - create new memory and copy content
    char *deep = malloc(strlen(original) + 1);
    strcpy(deep, original); // Copy actual content
    printf("Original: %s\n", original);
    printf("Deep:     %s\n", deep);
    // Modify deep copy
    deep[0] = 'Y';
    printf("After changing deep[0] to 'Y':\n");
    printf("Original: %s\n", original); // Unchanged!
    printf("Deep:     %s\n", deep);     // Changed
    // Cleanup
    free(deep);
    return 0;
}