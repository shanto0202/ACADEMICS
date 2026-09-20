/*
Algorithms in STL

The STL defines many algorithms for:
searching, sorting, counting, manipulating etc.

All algorithms are NON-MEMBER template functions.

They operate using iterators.

Algorithms usually work on a range:
[first, last)

Meaning:
first  -> included
last   -> excluded

Example:

sort(aVector.begin(), aVector.end()); // sort whole vector

sort(aVector.begin(), aVector.begin() + aVector.size()/2); // sort first half
*/

/*
Key Notes
---------
Algorithms operate on iterator ranges.
Work with any STL container.
[first,last) means last element is excluded.
Defined in <algorithm>.
*/