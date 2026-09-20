#include <iostream>
#include <fstream>
using namespace std;

int main()
{

    try
    {
        ofstream out("Inventory", ios::app); // open file for append

        if (!out)
            throw "Cannot open output file";

        out << "Radios " << 39 << endl;
        out << "Toasters " << 21 << endl;
        out << "Mixers " << 17 << endl;

        out.close();
    }

    catch (const char *message)
    {

        cout << message << endl;
        return 1;
    }

    try
    {

        ifstream in("Inventory"); // open file for reading

        if (!in)
            throw "Cannot open input file";

        // string item;
        char item[20];
        int quantity;

        in >> item >> quantity;

        while (!in.eof())
        {
            cout << item << ' ' << quantity << endl;
            in >> item >> quantity;
        }

        in.close();
    }

    catch (const char *message)
    {

        cout << message << endl;
        return 1;
    }

    return 0;
}

/*
Key Notes:

1. <fstream> library used for file operations.

2. ofstream → writing to file.

3. ifstream → reading from file.

4. ios::app → append mode.

5. eof() checks end of file.
*/