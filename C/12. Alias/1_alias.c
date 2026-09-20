#include <stdio.h>
// struct student
// {
//     int roll;
//     float cgpa;
// };
typedef int rollType;
typedef float cgpaType;
typedef struct
{
    rollType roll;
    cgpaType cgpa;
} studentType;
int main()
{
    studentType a;
    a.roll = 123;
    a.cgpa = 3.85;
    // For Tomal
    rollType r;
    cgpaType b;
    r = 456;
    b = 3.92;
    printf("Student a:\nRoll: %d, CGPA: %.2f\n", a.roll, a.cgpa);
    printf("Tomal:\nRoll: %d, CGPA: %.2f\n", r, b);
    return 0;
}