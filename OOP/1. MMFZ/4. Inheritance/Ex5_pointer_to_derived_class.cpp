#include <iostream>
using namespace std;

class base
{
public:
    base()
    {
        cout << "Constructing base class\n";
    }

    virtual ~base()
    {
        cout << "Destructing base class\n";
    }

    virtual void show()
    {
        cout << "Base show()\n";
    }
};

class derived : public base
{
public:
    derived()
    {
        cout << "Constructing derived class\n";
    }

    ~derived()
    {
        cout << "Destructing derived class\n";
    }

    void show()
    {
        cout << "Derived show()\n";
    }
};

int main()
{
    base *p; // base class pointer
    derived d;

    p = &d;    // base pointer → derived object
    p->show(); // runtime polymorphism (calls derived version)
    // derived *dp = &base_obj;

    return 0;
}

/*
Key Notes:

1. A base class pointer can point to a derived class object.

2. Reverse is not allowed:
   derived *dp = &base_obj; // ❌ invalid

3. If function is NOT virtual → base version is called (compile-time binding).

4. If function is virtual → derived version is called (runtime polymorphism).

5. Constructor order:
   base → derived

6. Destructor order:
   derived → base

7. Virtual destructor ensures proper destruction when using base pointer.

8. This concept is the foundation of runtime polymorphism.

Java Equivalent (Short):

Base ob = new Derived();
ob.show(); // calls Derived version (runtime polymorphism)

Note:
- Java has no pointers, uses references.
- Methods are virtual by default (dynamic binding).
*/