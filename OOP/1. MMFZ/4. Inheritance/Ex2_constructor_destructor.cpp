#include <iostream>
using namespace std;

class base
{
    int x, y;

public:
    base(int n, int p)
    {
        x = n;
        y = p;
        cout << "Constructing base class\n";
    }
    ~base()
    {
        cout << "Destructing base class\n";
    }
    void showxy()
    {
        cout << x << " " << y << '\n';
    }
};

class derived : public base
{
    int i, j;

public:
    derived(int n, int m, int p) : base(n, p) //10 20 30
    { // constructor chaining
        i = n;
        j = m;
        cout << "Constructing derived class\n";
    }
    ~derived()
    {
        cout << "Destructing derived class\n";
    }
    void showij()
    {
        cout << i << " " << j << '\n';
    }
};

int main()
{
    derived ob(10, 20, 30);
    ob.showxy();
    ob.showij();
    return 0;
}

/*
Key Notes:

1. Base constructor runs before derived constructor.

2. Base constructor is called using initializer list.

3. Destructors run in reverse order.

4. Output order shows constructor/destructor sequence clearly.
*/