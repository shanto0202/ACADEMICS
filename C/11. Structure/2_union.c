#include <stdio.h>
//A union is a user-defined data type that allows you to store different data types in the same memory location
union abc
{
    int a;
    char b;
    float c;
};
int main()
{
    union abc u;
    u.a = 1025;
    printf("After setting a\n");
    printf("a: %d b: %c (ASCII %d) c: %.2f\n", u.a, u.b, u.b, u.c);
    u.c = 78.98;
    printf("After setting c\n");
    printf("a: %d b: %c (ASCII %d) c: %.2f\n", u.a, u.b, u.b, u.c); // share same memory
    return 0;
}