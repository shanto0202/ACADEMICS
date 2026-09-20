/*
Function Objects in STL

Function objects (Functors) are objects that behave like functions.

They are classes that define operator().

STL provides built-in function objects such as:
less, minus, negate, divides, etc.

Functors that return true or false are called predicates.
*/

/*
Key Notes
---------
Functors overload operator().
They can be passed to STL algorithms.
Often used with sort(), transform(), etc.
Defined in <functional>.
*/
