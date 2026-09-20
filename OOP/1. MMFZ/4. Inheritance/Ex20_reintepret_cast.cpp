#include <iostream>
using namespace std;

struct mystruct
{
    int a = 5;
    char c = 'a'; //97
};

class A
{
public:
    void display()
    {
        cout << "Class A" << endl;
    }
};

class B
{
public:
    void display()
    {
        cout << "Class B" << endl;
    }
};

int main()
{
    int *p = new int(65);
    char *ch = reinterpret_cast<char *>(p); // reinterpret memory

    cout << *p << endl;
    cout << *ch << endl;
    cout << p << endl;

    mystruct s;
    int *iptr = reinterpret_cast<int *>(&s);

    cout << *iptr << endl; // 5 97
    iptr++;
    cout << *iptr << endl;
    
    B *b = new B();
    b->display();

    A *a = reinterpret_cast<A *>(b);
    a->display();

    return 0;
}

/*
Key Notes:

1. reinterpret_cast reinterprets raw memory as another type.

2. It does not perform safe conversion.

3. Mostly low-level and risky.

4. Use only when exact memory-level behavior is intended.
*/