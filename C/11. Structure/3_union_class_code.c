#include <stdio.h>
union restype
{
    int mark;
    float cgpa;
};
enum tagtype
{
    MARK,
    CGPA
};
struct student
{
    int roll;
    enum tagtype tag;
    union restype result;
};
int main()
{
    struct student a = {2, MARK, .result.mark = 86};
    struct student b = {3, CGPA, .result.cgpa = 3.89};
    if (a.tag == MARK)
        printf("Student A- Mark: %d\n", a.result.mark);
    else
        printf("Student A- CGPA: %.2f\n", a.result.cgpa);
    if (b.tag == MARK)
        printf("Student B- Mark: %d\n", b.result.mark);
    else
        printf("Student B- CGPA: %.2f\n", b.result.cgpa);
    union restype r = {.mark = 50};
    union restype s = r; // members copied
    printf("Union r mark: %d\n", r.mark);
    printf("Union s mark: %d\n", s.mark);
    return 0;
}