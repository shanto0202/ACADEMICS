#include <iostream>
using namespace std;

int funct(int *ptr)
{
    *ptr = *ptr + 10;
    return *ptr;
}

class Student
{
    int roll;

public:
    Student(int r)
    {
        roll = r; // 3
    };

    void funct() const
    {
        // this becomes const under const funct
        (const_cast<Student *>(this))->roll = 5; // remove constness
    }

    int getRoll() const
    {
        return roll;
    }
};

int main()
{
    const int num = 10;
    const int *ptr1 = &num;
    int *ptr2 = const_cast<int *>(ptr1); // pointer & reference
    // int *ptr3;
    // ptr3 = ptr2;
    cout << "Value of num after: " << funct(ptr2) << endl;
    cout << "*ptr1: " << *ptr1 << endl;
    cout << "Value of num before: " << num << endl;

    Student std(3);
    cout << "Roll number before: " << std.getRoll() << endl;
    std.funct();
    cout << "Roll number after: " << std.getRoll() << endl;
    return 0;
}

/*
Key Notes:

1. const_cast removes const qualification.

2. Mainly used with pointer/reference.

3. Modifying truly const objects through const_cast is dangerous/undefined.

4. Also used inside const member function with this pointer.
*/