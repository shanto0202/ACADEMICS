#include <bits/stdc++.h>
using namespace std;

class ArrayList
{
private:
    int *arr;
    int capacity;
    int len;
    int cur;

    void increase_capacity()
    {
        int c2 = capacity * 2;
        int *t = new int[c2];
        for (int i = 0; i < len; i++)
        {
            t[i] = arr[i];
        }
        delete[] arr;
        arr = t;
        cout << "Capacity increased from " << capacity << " to " << c2 << endl;
        capacity = c2;
    }

    void decrease_capacity()
    {
        int c2 = capacity / 2;
        if (c2 < 2)
        {
            c2 = 2;
        }
        if (c2 == capacity)
        {
            return;
        }
        int *t = new int[c2];
        for (int i = 0; i < len; i++)
        {
            t[i] = arr[i];
        }
        delete[] arr;
        arr = t;
        cout << "Capacity decreased from " << capacity << " to " << c2 << endl;
        capacity = c2;
    }

public:
    ArrayList()
    {
        capacity = 2;
        len = 0;
        cur = -1;
        arr = new int[capacity];
    }

    ~ArrayList()
    {
        delete[] arr;
    }

    void print()
    {
        if (len == 0)
        {
            cout << "[ . ]" << endl;
            return;
        }
        cout << "[ ";
        for (int i = 0; i < len; i++)
        {
            cout << arr[i] << " ";
            if (i == cur)
            {
                cout << "| ";
            }
        }
        cout << "]" << endl;
    }
    void insert(int item)
    {
        if (len >= capacity / 2)
        {
            increase_capacity();
        }
        for (int i = len; i > cur + 1; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[cur + 1] = item;
        len++;
        cur++;
    }
    int delete_cur()
    {
        if (len == 0 || cur == -1)
        {
            return -1;
        }
        int x = arr[cur];
        for (int i = cur; i < len - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        len--;
        if (cur >= len)
            cur = len - 1;
        if (len < capacity / 4)
        {
            decrease_capacity();
        }
        return x;
    }
    void append(int item)
    {
        if (len > capacity / 2)
        {
            increase_capacity();
        }
        arr[len++] = item;
        if (cur == -1)
        {
            cur = 0;
        }
    }
    int size() const
    {
        return len;
    }
    void prev(int n)
    {
        if (len == 0)
        {
            return;
        }
        cur -= n;
        if (cur < 0)
        {
            cur = 0;
        }
    }
    void next(int n)
    {
        if (len == 0)
        {
            return;
        }
        cur += n;
        if (cur >= len)
        {
            cur = len - 1;
        }
    }
    int is_present(int it)
    {
        int x = search(it);
        if (x != -1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void clear()
    {
        delete[] arr;
        capacity = 2;
        len = 0;
        cur = -1;
        arr = new int[capacity];
    }
    int delete_item(int item)
    {
        int idx = search(item);
        if (idx == -1)
        {
            return -1;
        }
        cur = idx;
        return delete_cur();
    }
    void swap_ind(int i, int j)
    {
        if (i < 0 || j < 0 || i >= len || j >= len)
        {
            return;
        }
        int t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
    int search(int item)
    {
        for (int i = 0; i < len; i++)
            if (arr[i] == item)
            {
                cur = i;
                return i;
            }
        return -1;
    }
    int find(int idx)
    {
        if (idx < 0 || idx >= len)
        {
            return -1;
        }
        cur = idx;
        return arr[idx];
    }
    int update(int idx, int x)
    {
        if (idx < 0 || idx >= len)
            return -1;
        int old = arr[idx];
        arr[idx] = x;
        cur = idx;
        return old;
    }
    int trim()
    {
        if (len == 0)
        {
            return -1;
        }
        int val = arr[len - 1];
        len--;
        if (cur >= len)
        {
            cur = len - 1;
        }
        if (len < capacity / 4)
        {
            decrease_capacity();
        }
        return val;
    }
    void reverse()
    {
        int t = 0;
        for (int i = 0; i < len / 2; i++)
        {
            t = arr[i];
            arr[i] = arr[len - 1 - i];
            arr[len - 1 - i] = t;
        }
    }
};