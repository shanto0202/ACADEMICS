// Passing Arrays to Methods
// Array elements can be modified inside methods.
// But changing the array reference itself does not affect the caller.

public class Ex3_ArrayMethodExample {

    public static void modifyArray(double d[]) {

        d[0] = 1.1; // visible to caller

        // new array assignment not visible outside
        d = new double[10];
        d[0] = 9.9;
    }

    public static void main(String[] args) {

        double[] temperature = new double[5];

        modifyArray(temperature);

        System.out.println("First element: " + temperature[0]);
    }
}

/*
Key Notes
---------
Array elements → change visible

Array reference reassignment → not visible

Reason:
Java passes reference by value.
 */
