// Store Objects in Vector

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

// class representing temperature
class DailyTemp
{
    int temp; // stores temperature

public:
    DailyTemp()
    {
        temp = 0;
    } // default constructor

    DailyTemp(int x)
    {
        temp = x;
    } // parameterized constructor

    // overload assignment operator
    DailyTemp &operator=(int x)
    {
        temp = x;
        return *this;
    }

    // accessor function
    double get_temp()
    {
        return temp;
    }
};

// comparison operator for sorting
bool operator<(DailyTemp a, DailyTemp b)
{
    return a.get_temp() < b.get_temp();
}

// equality operator
bool operator==(DailyTemp a, DailyTemp b)
{
    return a.get_temp() == b.get_temp();
}

int main()
{
    vector<DailyTemp> v; // create vector of objects

    unsigned int i;

    // insert random Fahrenheit temperatures
    for (i = 0; i < 7; i++)
        v.push_back(DailyTemp(60 + rand() % 30));

    cout << "Fahrenheit temperatures:\n";

    // access objects from vector
    for (i = 0; i < v.size(); i++)
        cout << v[i].get_temp() << " ";

    cout << endl;

    // convert Fahrenheit to Centigrade
    for (i = 0; i < v.size(); i++)
        v[i] = (int)((v[i].get_temp() - 32) * 5 / 9);

    cout << "Centigrade temperatures:\n";

    for (i = 0; i < v.size(); i++)
        cout << v[i].get_temp() << " ";

    return 0;
}

/*
Key Notes:

1. vector<DailyTemp> creates a vector that stores objects of class DailyTemp.
2. push_back() inserts objects into the vector.
3. v[i] accesses the object stored at index i.
4. get_temp() is a member function used to retrieve the temperature value.
5. Operator overloading:
      operator=  → assigns integer value to object
      operator<  → allows comparison between objects
      operator== → checks equality of objects
6. Random temperatures are generated using rand().
7. Formula used for conversion:
      C = (F - 32) * 5 / 9
*/