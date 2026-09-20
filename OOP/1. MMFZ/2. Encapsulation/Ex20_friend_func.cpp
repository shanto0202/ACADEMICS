#include <iostream>
using namespace std;

class Truck; // Forward declaration

/* ---------- Car Class ---------- */
class Car
{
    int passenger, speed;

public:
    Car(int p, int s)
    {
        passenger = p;
        speed = s;
    }

    // Member friend example
    int speedGreaterMember(Truck t);

    // Non-member friend example
    friend int speedGreater(Car c, Truck t);
};

/* ---------- Truck Class ---------- */
class Truck
{
    int weight, speed;

public:
    Truck(int w, int s)
    {
        weight = w;
        speed = s;
    }

    // Friend declarations
    friend int Car::speedGreaterMember(Truck t); // member friend
    friend int speedGreater(Car c, Truck t);     // non-member friend
};

/* ---------- Friend Function (non-member) ---------- */
int speedGreater(Car c, Truck t)
{
    return c.speed - t.speed;
}

/* ---------- Member Friend Function ---------- */
int Car::speedGreaterMember(Truck t)
{
    return speed - t.speed;
}

int main()
{
    Car c(5, 70);
    Truck t(500, 60);
    // Using non-member friend
    cout << "Speed Gap (Friend Function): " << speedGreater(c, t) << endl;
    // Using member friend
    cout << "Speed Gap (Member Friend): " << c.speedGreaterMember(t) << endl;
    return 0;
}

/*
Key Notes:
1. Friend function → not a class member but can access private data.
2. Declared using keyword "friend" inside the class.
3. Two cases shown here:
   a) Normal non-member friend function.
   b) Member function of one class as friend of another class.
4. Forward declaration (class Truck;) is required when classes reference each other.
5. Friend functions break strict encapsulation but are useful for controlled access.
*/