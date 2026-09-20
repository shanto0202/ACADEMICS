#include <iostream>
#include <typeinfo>
using namespace std;

class Animal
{
public:
    virtual void sound() = 0;
};

class Dog : public Animal
{
    void sound()
    {
        cout << "Bark" << endl;
    }
};

class Cat : public Animal
{
    void sound()
    {
        cout << "Meow" << endl;
    }
};

int main()
{
    Dog *dog = new Dog();
    Cat *cat = new Cat();
    double length = 25.5;
    int num = 10;
    Animal *animal;

    const type_info &type_num = typeid(num);                   // int
    cout << "Type(num): " << type_num.name() << endl;          // i
    cout << "Type(dog): " << typeid(dog).name() << endl;       // Dog*->P3Dog   (P = pointer, 3= object name legth, object)
    cout << "Type(*dog): " << typeid(*dog).name() << endl;     // 3Dog
    cout << "Type(cat): " << typeid(cat).name() << endl;       // P3Cat
    cout << "Type(length): " << typeid(length).name() << endl; // d

    animal = dog;
    cout << "Type(animal): " << typeid(animal).name() << endl;   // P6Animal
    cout << "Type(*animal): " << typeid(*animal).name() << endl; // 3Dog

    animal = cat;
    cout << "Type(animal): " << typeid(animal).name() << endl;   // P6Animal
    cout << "Type(*animal): " << typeid(*animal).name() << endl; // 3Cat

    cout << "Type(length+num): " << typeid(length + num).name() << endl; // d
    return 0;
}

/*
Key Notes:

1. typeid gives runtime type information.

2. typeid(pointer) and typeid(*pointer) can differ.

3. For polymorphic base pointer, typeid(*pointer) shows actual object type.
*/
