#include <stdio.h>
struct student
{
    char name[31];
    int roll;
    float cgpa;
};
int main()
{
    struct student a = {"Tomal", 1, 3.88};
    struct student b, c;
    // c = {"Basir", 3, 3.90};
    c = (struct student){"Basir", 3, 3.90};
    b = a;
    scanf("%s %i %f", a.name, &a.roll, &a.cgpa);
    printf("a: %s %i %.2f\n", a.name, a.roll, a.cgpa);
    printf("b: %s %i %.2f\n", b.name, b.roll, b.cgpa);
    printf("c: %s %i %.2f\n", c.name, c.roll, c.cgpa);
    struct student whole_class[100];
    whole_class[10] = (struct student){"Bijoy", 2, 3.87};
    printf("ar: %s %i %.2f\n", whole_class[10].name, whole_class[10].roll, whole_class[10].cgpa);
}