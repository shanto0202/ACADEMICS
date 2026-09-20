#include <stdio.h>
typedef struct
{
    char name[31];
    int roll;
    float cgpa;
} studentType; // 40 bytes (31 + 1 byte for padding + 4 + 4)
int main()
{
    printf("size of struct %d\n", sizeof(studentType));
    studentType Salam, Tomal;
    studentType *s = &Salam; // Pointer to structure
    printf("Enter student details:\n");
    // Method 1: Using (*pointer).member syntax
    printf("Enter name: ");
    scanf("%s", (*s).name); // (*s).name is equivalent to s->name
    printf("Enter roll: ");
    scanf("%d", &(*s).roll); // &(*s).roll is equivalent to &(s->roll)
    printf("Enter CGPA: ");
    scanf("%f", &(*s).cgpa);

    // Method 2: Using arrow operator (recommended)
    printf("\nDisplaying using arrow operator:\n");
    printf("Name: %s\n", s->name);
    printf("Roll: %d\n", s->roll);
    printf("CGPA: %.2f\n", s->cgpa);

    // Both methods are equivalent
    printf("\nDisplaying using (*pointer).member:\n");
    printf("Name: %s\n", (*s).name);
    printf("Roll: %d\n", (*s).roll);
    printf("CGPA: %.2f\n", (*s).cgpa);

    return 0;
}