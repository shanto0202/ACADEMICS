// deep copy vs shallow copy
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Copying From Structures
typedef struct
{
    char *name;
    int *roll;
} student;
int main()
{
    // Create and initialize first student
    student s;
    s.name = (char *)malloc(31 * sizeof(char));
    s.roll = (int *)malloc(sizeof(int));
    strcpy(s.name, "tomal");
    *(s.roll) = 12;

    printf("Original student s:\n");
    printf("Name: %s, Roll: %d\n", s.name, *(s.roll));

    // SHALLOW COPY - copies pointers only
    student t_shallow;
    t_shallow = s; // This copies pointers, not the data

    printf("\nAfter shallow copy:\n");
    printf("t_shallow - Name: %s, Roll: %d\n", t_shallow.name, *(t_shallow.roll));

    // Modify original - affects shallow copy too!
    strcpy(s.name, "changed");
    *(s.roll) = 99;

    printf("\nAfter modifying s (shallow copy affected):\n");
    printf("s - Name: %s, Roll: %d\n", s.name, *(s.roll));
    printf("t_shallow - Name: %s, Roll: %d\n", t_shallow.name, *(t_shallow.roll));

    // Reset for deep copy demonstration
    strcpy(s.name, "tomal");
    *(s.roll) = 12;

    // DEEP COPY - copies actual data to new memory
    student t_deep;
    t_deep.name = (char *)malloc(31 * sizeof(char));
    t_deep.roll = (int *)malloc(sizeof(int));
    strcpy(t_deep.name, s.name);
    *(t_deep.roll) = *(s.roll);

    printf("\nAfter deep copy:\n");
    printf("t_deep - Name: %s, Roll: %d\n", t_deep.name, *(t_deep.roll));

    // Modify original - deep copy remains unchanged
    strcpy(s.name, "modified");
    *(s.roll) = 88;

    printf("\nAfter modifying s (deep copy unaffected):\n");
    printf("s - Name: %s, Roll: %d\n", s.name, *(s.roll));
    printf("t_deep - Name: %s, Roll: %d\n", t_deep.name, *(t_deep.roll));

    // Free memory
    free(s.name);
    free(s.roll);
    free(t_deep.name);
    free(t_deep.roll);
    // Note: Don't free t_shallow members as they point to same memory as s
    return 0;
}