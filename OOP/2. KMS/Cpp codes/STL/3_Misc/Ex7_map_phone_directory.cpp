// Use a map to create a phone directory.

#include <iostream>
#include <map>
#include <cstring>
using namespace std;

class name
{

    char str[40];

public:
    name()
    {
        strcpy(str, "");
    }

    name(char *s)
    {
        strcpy(str, s);
    }

    char *get()
    {
        return str;
    }
};

// Must define less than relative to name objects.
bool operator<(name a, name b)
{

    return strcmp(a.get(), b.get()) < 0;
}

class phoneNum
{

    char str[80];

public:
    phoneNum()
    {
        strcpy(str, "");
    }

    phoneNum(char *s)
    {
        strcpy(str, s);
    }

    char *get()
    {
        return str;
    }
};

int main()
{

    map<name, phoneNum> directory;
    // name Name = new name("Tom");
    //  put names and numbers into map
    directory[name("sifat")] = phoneNum("0123");
    directory.insert(pair<name, phoneNum>(name("Tom"), phoneNum("555-4533")));
    directory.insert(pair<name, phoneNum>(name("Chris"), phoneNum("555-9678")));
    directory.insert(pair<name, phoneNum>(name("John"), phoneNum("555-8195")));
    directory.insert(pair<name, phoneNum>(name("Rachel"), phoneNum("555-0809")));

    // given a name, find number
    char str[80];

    cout << "Enter name: ";
    cin >> str;

    map<name, phoneNum>::iterator p;

    p = directory.find(name(str)); // O(n)

    if (p != directory.end())
        cout << "Phone number: " << p->second.get();
    else
        cout << "Name not in directory.\n";

    return 0;
}

/*
Key Notes
---------
map can store user-defined objects.
Custom comparison operator required for keys.
find() searches using key.
iterator->second accesses mapped value.
*/