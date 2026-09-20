#include <fstream>
#include <iostream>
using namespace std;

int main()
{

    ifstream in;
    ofstream out;

    fstream out2("test3.cpp", ios::out | ios::app);

    char ch;

    try
    {

        in.open("test.cpp");

        if (!in)
            throw "Cannot open input file";

        out.open("test2.cpp", ios::out);

        if (!out)
            throw "Cannot open output file";
    }

    catch (const char *message)
    {

        cout << message << endl;
        return 1;
    }

    in.get(ch); // read character

    while (!in.eof())
    {

        out.put(ch); // write character
        out2.put(ch);

        in.get(ch);
    }

    if (in.is_open())

        cout << "file already open\n";

    in.close();
    out.close();
    out2.close();

    return 0;
}

/*
Key Notes:

1. get() reads a character from file.

2. put() writes a character to file.

3. Used for sequential file access.

4. Multiple output files can be written simultaneously.
*/