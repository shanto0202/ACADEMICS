#include <iostream>
using namespace std;

void f2(int a = 0, int b = 0) //from left side
{
    cout << "a = " << a << ", b = " << b << endl;
}

int main()
{
    f2();      // equivalent to void f2()
    f2(5);     // equivalent to void f2(int a)
    f2(5, 10); // equivalent to void f2(int a, int b)
}