#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct
{
    char name[31];
    int roll;
    float cgpa;
} studentType;
int main()
{
    studentType *s = (studentType *)malloc(sizeof(studentType));
    assert(s != NULL);
    // Initialize or get input for the structure members
    printf("Enter name: ");
    scanf("%s", s->name); // (*s).name
    printf("Enter roll: ");
    scanf("%d", &(s->roll));
    printf("Enter CGPA: ");
    scanf("%f", &(s->cgpa));
    // Print the values
    printf("Name: %s\n", s->name);
    printf("Roll: %d\n", s->roll);
    printf("CGPA: %.2f\n", s->cgpa);
    free(s);
    return 0;
}