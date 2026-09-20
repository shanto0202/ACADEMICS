#include <iostream>
#include <string>
using namespace std;

int main()
{
    int i;

    string s1 = "Quick of Mind, Strong of Body, Pure of Heart";
    string s2;

    i = s1.find("Quick");

    if (i != string::npos)
        cout << "Match found at " << i << endl;

    // find last "of"
    i = s1.rfind("of"); // 36

    if (i != string::npos)
    {
        cout << "Match found at " << i << endl;

        cout << "Remaining string is:\n";

        s2.assign(s1, i, s1.size()); // (string, starting, ending)

        cout << s2;
    }

    return 0;
}

/*
Key Notes
---------
find() searches forward.
rfind() searches backward.
npos means not found.
assign() copies substring.
*/