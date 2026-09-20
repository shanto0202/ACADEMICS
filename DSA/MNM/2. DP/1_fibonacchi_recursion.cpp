#include <iostream>
using namespace std;

int fib[100]; // array to store computed values

int Fibonacci(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    if (fib[n] == -1) // not computed yet
    {
        fib[n] = Fibonacci(n - 1) + Fibonacci(n - 2);
    }

    return fib[n];
}

int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;

    for (int i = 0; i < 100; i++)
        fib[i] = -1; // initialize

    cout << "Fibonacci = " << Fibonacci(n);

    return 0;
}