#include <iostream>
using namespace std;

class Student
{
    static int count; // static variable
    int y;

public:
    Student()
    {
        count++; // increment when object created
    }

    static void showCount()
    { // static function
        cout << "Total students: " << count << endl;
    }
};

// static variable must be defined outside
int Student::count = 0;

int main()
{
    Student s1, s2, s3;
    s1.showCount();
    Student::showCount(); // call static function
}