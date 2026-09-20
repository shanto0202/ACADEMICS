#include <iostream>
using namespace std;

class Animal
{
public:
    virtual void print()
    {
        cout << "Animal" << endl;
    }
};

class Dog : public Animal
{
public:
    void print()
    {
        cout << "Dog" << endl;
    }
};

class Cat : public Animal
{
public:
    void print()
    {
        cout << "Cat" << endl;
    }
};

class myClass
{
};

int main()
{
    Animal *animal = new Animal;
    Dog *dog = new Dog;
    Cat *cat = new Cat;

    animal->print();
    // dog->print();
    animal = dynamic_cast<Animal *>(dog);
    animal->print();

    animal = dynamic_cast<Animal *>(cat);
    animal->print();

    Dog *d = dynamic_cast<Dog *>(animal); // checked downcast
    if (d == nullptr)
    {
        cout << "Conversion failed" << endl;
    }
    else
        d->print();

    myClass *x = dynamic_cast<myClass *>(animal);
    return 0;
}

/*
Key Notes:

1. dynamic_cast performs runtime-checked casting.

2. Failed pointer cast returns nullptr.

3. Used mainly in polymorphic class hierarchies.
*/