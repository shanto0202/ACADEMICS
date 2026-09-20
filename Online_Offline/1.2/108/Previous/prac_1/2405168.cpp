#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define jora(p, n) pair<ll, ll> p(n)
#define sajai(x) sort(x.begin(), x.end())
#define arr(v, x, y) vector<vector<ll>> v(x, vector<int>(y))
#define loop(i, n) for (ll i = 0; i < n; i++)
#define in(v) loop(i, v.size()) cin >> v[i]
#define out(v) loop(i, v.size()) cout << v[i] << " "
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define tata "\n"
using namespace std;

class Vector
{
    int n;
    double *elements;

public:
    Vector(int dimension, const double *p) : n(dimension)
    {
        elements = (double *)malloc(n * sizeof(double));
        if (elements == nullptr)
        {
            cout << "Memory allocation failed in constructor." << tata;
            exit(EXIT_FAILURE);
        }
        loop(i, n)
        {
            elements[i] = p[i];
        }
    }
    ~Vector()
    {
        free(elements);
    }
    void add(const Vector &v)
    {
        if (n != v.n)
        {
            cout << "Error: Vector dimensions do not match for addition." << tata;
            return;
        }
        loop(i, n)
        {
            elements[i] += v.elements[i];
        }
    }
    void add(double val)
    {
        for (int i = 0; i < n; ++i)
        {
            elements[i] += val;
        }
    }
    void subtract(const Vector &v)
    {
        if (n != v.n)
        {
            cout << "Error: Vector dimensions do not match for subtraction." << tata;
            return;
        }
        loop(i, n)
        {
            elements[i] -= v.elements[i];
        }
    }
    void subtract(double val)
    {
        for (int i = 0; i < n; ++i)
        {
            elements[i] -= val;
        }
    }
    double product(const Vector &v) const
    {
        if (n != v.n)
        {
            cout << "Error: Vector dimensions do not match for dot product." << tata;
            return 0.0;
        }
        double d = 0.0;
        loop(i, n)
        {
            d += elements[i] * v.elements[i];
        }
        return d;
    }
    void product(double val)
    {
        loop(i, n)
        {
            elements[i] *= val;
        }
    }
    void set_element(int idx, double val)
    {
        if (idx >= 0 && idx < n)
        {
            elements[idx] = val;
        }
        else
        {
            cout << "Error: Index out of bounds in set_element." << tata;
        }
    }
    double get_element(int idx) const
    {
        if (idx >= 0 && idx < n)
        {
            return elements[idx];
        }
        else
        {
            cout << "Error: Index out of bounds in get_element." << tata;
            return 0.0;
        }
    }
    void display() const
    {
        // cout << "Vector (Dimension " << n << "): [";
        loop(i, n)
        {
            cout << elements[i];
            if (i < n - 1)
            {
                cout << ", ";
            }
        }
        cout << tata;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    double arr1[] = {1.2, 2.3, 3.4, 4.5};
    Vector v1(4, arr1); // 4-dimensional vector initialized with arr1
    cout << "Vector v1: ";
    v1.display(); // Output: [1.2, 2.3, 3.4, 4.5]
    double arr2[] = {5.0, 6.0, 7.0, 8.0};
    Vector v2(4, arr2); // Another 4-dimensional vector initialized with arr2
    cout << "Vector v2: ";
    v2.display(); // Output: [5.0, 6.0, 7.0, 8.0]
    v1.add(v2);
    cout << "After adding v2 to v1: ";
    v1.display(); // Output: [6.2, 8.3, 10.4, 12.5]
    v1.add(2.0);
    cout << "After adding scalar 2.0 to v1: ";
    v1.display(); // Output: [8.2, 10.3, 12.4, 14.5]
    v1.subtract(v2);
    cout << "After subtracting v2 from v1: ";
    v1.display(); // Output: [3.2, 4.3, 5.4, 6.5]
    v1.subtract(1.5);
    cout << "After subtracting scalar 1.5 from v1: ";
    v1.display(); // Output: [1.7, 2.8, 3.9, 5.0]
    double dotProduct = v1.product(v2);
    cout << "Dot product of v1 and v2: " << dotProduct << endl; // Output: 92.6
    v1.product(3.0);
    cout << "After multiplying v1 with scalar 3.0: ";
    v1.display(); // Output: [5.1, 8.4, 11.7, 15.0]
    return 0;
}