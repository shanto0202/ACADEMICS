#include <iostream>
#include <string>
using namespace std;

int main()
{

    string str1("Alpha");
    string str2("Beta");
    string str3("Omega");
    string str4;

    // assign string
    str4 = str1;

    cout << str1 << "\n"<< str3 << "\n";

    // concatenate strings
    str4 = str1 + str2;
    cout << str4 << "\n";

    // concatenate with C string
    str4 = str1 + " to " + str3;
    cout << str4 << "\n";

    // compare strings
    if (str3 > str1)
        cout << "str3 > str1\n";

    if (str3 == str1 + str2)
        cout << "str3 == str1+str2\n";

    // assign C-string
    str1 = "This is a null-terminated string.\n";

    cout << str1;

    // copy constructor
    string str5(str1);

    cout << str5;

    // input string
    cout << "Enter a string: ";
    cin >> str5;

    cout << str5;

    return 0;
}

/*
Key Notes
---------
Strings support assignment and comparison.
+ operator concatenates strings.
cin reads string until whitespace.
*/