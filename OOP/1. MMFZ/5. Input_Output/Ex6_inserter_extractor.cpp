#include <iostream>
#include <string.h>
using namespace std;

class Inventory
{
    char itemName[20];
    int itemNumber;
    double price;

public:
    Inventory(char *name, int num, double cost)
    {
        strcpy(itemName, name);
        itemNumber = num;
        price = cost;
    }

    friend ostream &operator<<(ostream &os, Inventory &inv); // inserter
    friend istream &operator>>(istream &is, Inventory &inv); // extractor
};

ostream &operator<<(ostream &os, Inventory &inv)
{
    os << "Item: " << inv.itemName << endl;
    os << "Item Number: " << inv.itemNumber << endl;
    os << "Price: " << inv.price << endl;

    return os;
}

istream &operator>>(istream &is, Inventory &inv)
{

    cout << "Enter item name: ";
    is >> inv.itemName;

    cout << "Enter item number: ";
    is >> inv.itemNumber;

    cout << "Enter price: ";
    is >> inv.price;

    return is;
}

int main()
{

    Inventory item1("hammer", 1234, 19.95);
    Inventory item2("wrench", 4567, 8.75);

    cout << item1 << item2; // overloaded <<

    cin >> item1 >> item2; // overloaded >>

    cout << item1 << item2;

    return 0;
}

/*
Key Notes:

1. << is insertion operator (output stream).

2. >> is extraction operator (input stream).

3. Both usually implemented as friend functions.

4. Return stream reference to allow chaining:
    cout << a << b << c;
*/