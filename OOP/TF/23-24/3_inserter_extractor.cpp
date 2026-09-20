#include <iostream>
using namespace std;

class Complex
{
    int real;
    int imaginary;

public:
    // extractor (>>)
    friend istream &operator>>(istream &in, Complex &c)
    {
        cout << "Enter real part: ";
        in >> c.real;
        if (!in)
        {
            in.setstate(ios::failbit);
            return in;
        }

        cout << "Enter imaginary part: ";
        in >> c.imaginary;
        if (!in)
        {
            in.setstate(ios::failbit);
            return in;
        }

        return in;
    }

    // inserter (<<)
    friend ostream &operator<<(ostream &out, Complex &c)
    {
        out << c.real << " + " << c.imaginary << "i";
        return out;
    }
};

int main()
{
    Complex c;

    cin >> c; // extractor
    if (cin.fail())
    {
        cout << "Invalid input\n";
        return 0;
    }
    cout << c; // inserter

    return 0;
}

/*
Key Notes:

1. operator>> → extractor (input)
2. operator<< → inserter (output)

3. Must return:
   istream& and ostream& respectively

4. failbit → signals invalid input

5. friend needed to access private members

6. Output format: real + imaginary i
*/