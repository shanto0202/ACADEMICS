// Arrays Example
// Arrays are fixed-length collections of elements of the same type.
// In Java, arrays are objects (reference types).
// Elements may be primitive types or reference types.

public class Ex1_ArrayDemo {

    public static void main(String[] args) {

        // Declaring and creating an array
        int[] a = new int[10]; // array object created in heap

        // Every array knows its own length
        for (int i = 0; i < a.length; i++) {
            a[i] = i; // access using a[index]
        }

        // Printing array elements
        for (int i = 0; i < a.length; i++) {
            System.out.println(a[i]);
        }

        // Array initializer example
        int n[] = {10, 20, 30, 40, 50};

        System.out.println("Initializer example:");
        for (int i = 0; i < n.length; i++) {
            System.out.println(n[i]);
        }
    }
}

/*
Key Notes
---------
Array syntax:
name[index]

Index type:
int / byte / short / char (not long)

Default values when created using new:
int → 0
boolean → false
reference → null

Array length stored in:
array.length
 */
