#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define sajai(x) sort(x.begin(), x.end())
#define loop(i, j, n) for (ll i = j; i < n; i++)
#define in(v) loop(i, 0, v.size()) cin >> v[i]
#define out(v) loop(i, 0, v.size()) cout << v[i] << " "
#define tata '\n'
using namespace std;

class Figure
{
private:
    int row, col;
    string name;
    int *matrix;

public:
    Figure()
    {
        row = 0;
        col = 0;
        matrix = nullptr;
        name = "Empty Figure";
    }
    Figure(int r, int c, int *arr)
    {
        row = r;
        col = c;
        matrix = new int[row * col];
        loop(i, 0, row * col)
        {
            matrix[i] = arr[i];
        }
        if (row == 2)
            name = "Line";
        else if (row == 3)
            name = "Triangle";
        else if (row == 4)
            name = "Rectangle";
        name += to_string(col) + "D";
    }
    Figure(const Figure &f)
    {
        row = f.row;
        col = f.col;
        name = f.name;
        matrix = new int[row * col];
        for (int i = 0; i < row * col; i++)
            matrix[i] = f.matrix[i];
    }

    ~Figure()
    {
        if (matrix)
        {
            for (int i = 0; i < row * col; i++)
                matrix[i] = 0;
            delete[] matrix;
        }
        row = col = 0;
        cout << "\"" << name << "\" has been destroyed" << tata;
    }
    int getSum()
    {
        int s = 0;
        loop(i, 0, row * col)
        {
            s += matrix[i];
        }
        return s;
    }
    int getSum(int x, int y)
    {
        if (x > row || y > col)
        {
            cout << "ERROR!" << tata;
            return -1;
        }
        else
        {
            int sum = 0;
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    sum += matrix[i * col + j];
                }
            }
            return sum;
        }
    }
    void Printsum(int x)
    {
        cout << "Sum of all elements: " << x << tata;
    }
    void Printsum(int x, int a, int b)
    {
        cout << "Sum of " << a << "x" << b << ": " << x << tata;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Figure f1;
    int arr[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    Figure f2(3, 2, (int *)arr);
    int p = f2.getSum();
    f2.Printsum(p);
    p = f2.getSum(2, 2);
    f2.Printsum(p, 2, 2);
    return 0;
}