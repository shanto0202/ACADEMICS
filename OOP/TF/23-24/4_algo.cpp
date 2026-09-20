#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

// Function to print any list
void printList(const list<int> &lst)
{
    for (int x : lst)
        cout << x << " ";
    cout << endl;
}

// Predicate function for even check
bool isEven(int x)
{
    return x % 2 == 0;
}

// Function used in transform to make square
int square(int x)
{
    return x * x;
}

int main()
{
    list<int> v = {20, 16, 12, 8, 4, 3, 6, 9, 12, 15};

    int cnt12 = count(v.begin(), v.end(), 12);

    int evenCnt = count_if(v.begin(), v.end(), isEven);

    list<int> newList;
    remove_copy(v.begin(), v.end(), back_inserter(newList), 12);

    list<int> reversedList = v;
    reversedList.reverse();

    list<int> squaredList;
    transform(v.begin(), v.end(), back_inserter(squaredList), square);
    return 0;
}

/*
Key Notes:

1. list<int> original = {...}
   -> stores the given elements in a list container.

2. count(begin, end, value)
   -> counts how many times a value appears.
   -> Here, 12 appears 2 times.

3. count_if(begin, end, condition)
   -> counts elements satisfying a condition.
   -> isEven() checks whether a number is even.
   -> Even numbers here = 20,16,12,8,4,6,12 = 7.

4. remove_copy(begin, end, destination, value)
   -> copies all elements except the given value.
   -> original list does NOT change.
   -> new list becomes: 20 16 8 4 3 6 9 15

5. reverse()
   -> reverses the list.
   -> reversed list: 15 12 9 6 3 4 8 12 16 20

6. transform(begin, end, destination, function)
   -> applies a function to every element.
   -> Here square(x) = x*x.
   -> squared list: 400 256 144 64 16 9 36 81 144 225

7. Important exam trap:
   -> remove() algorithm on normal containers does not actually erase size by itself.
   -> For list, using remove_copy is safest here because question says:
      create separate container without changing original list.

8. Final answers:
   -> Count of 12 = 2
   -> Count of even numbers = 7
   -> New list without 12 = 20 16 8 4 3 6 9 15
   -> Reversed original = 15 12 9 6 3 4 8 12 16 20
   -> Squared list = 400 256 144 64 16 9 36 81 144 225
*/