#include <iostream>
#include <list>
using namespace std;

int main()
{
    char string[] = "?drawkcab tsil a tnirp uoy dluow woH";

    list<char> lst; // create an empty list

    int i = 0;

    while (string[i])
        lst.push_back(string[i++]); // store characters in list

    cout << "List printed backwards:\n";

    list<char>::iterator p = lst.end(); // start from end

    while (p != lst.begin())
    {
        p--; // decrement iterator before using
        cout << *p;
    }

    return 0;
}

/*
Key Notes
---------
end() points AFTER last element.
So we must decrement first (p--).
List supports bidirectional iterators.
Hence reverse traversal is possible.
*/