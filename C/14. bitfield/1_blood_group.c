#include <stdio.h>
#include <string.h>
// Regular struct (wastes memory)
struct personRegular
{
    unsigned int bloodgroup; // uses 32 bits, but only needs 2
    unsigned int rhfactor;   // uses 32 bits, but only needs 1
    unsigned int haircolor;  // uses 32 bits, but only needs 2
    unsigned int eyecolor;   // uses 32 bits, but only needs 2
};
// Bitfield struct (space efficient)
struct personType
{
    unsigned int bloodgroup : 2; // only 2 bits (0-3)
    unsigned int rhfactor : 1;   // only 1 bit (0-1)
    unsigned int haircolor : 2;  // only 2 bits (0-3)
    unsigned int eyecolor : 2;   // only 2 bits (0-3)
};
// Student structure for array example
struct student
{
    char name[20];
    int roll;
};
int main()
{
    // Demonstrate bitfield usage
    struct personType person1;
    // Blood groups: 0=O, 1=A, 2=B, 3=AB
    person1.bloodgroup = 2; // A type
    person1.rhfactor = 1;   // Positive (Rh+)
    person1.haircolor = 2;  // Brown
    person1.eyecolor = 2;   // Black

    printf("Person Details:\n");
    printf("Blood Group: %u\n", person1.bloodgroup);
    printf("Rh Factor: %s\n", person1.rhfactor ? "Positive" : "Negative");
    printf("Hair Color: %u\n", person1.haircolor);
    printf("Eye Color: %u\n", person1.eyecolor);

    // Memory comparison
    printf("\nMemory Usage:\n");
    printf("Regular struct size: %d bytes\n", sizeof(struct personRegular));
    printf("Bitfield struct size: %d bytes\n", sizeof(struct personType));

    // Array of structures example
    struct student students[5];

    // Input example (corrected syntax)
    strcpy(students[0].name, "Alice");
    students[0].roll = 101;

    strcpy(students[1].name, "Bob");
    students[1].roll = 102;
    
    for (int i = 0; i < 2; i++)
    {
        printf("Student %d: Name=%s, Roll=%d\n", i, students[i].name, students[i].roll);
    }
    return 0;
}