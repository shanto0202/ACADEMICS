// Arrays of Reference Types
// When creating reference arrays, only references are created first.
// Actual objects must be created separately.

class A {

    private int a;

    public int getA() {
        return a;
    }

    public void setA(int a) {
        this.a = a;
    }
}

public class Ex2_ArrayReferenceType {

    public static void main(String[] args) {

        // Array of objects
        A[] array = new A[10]; // creates 10 references (initially null)

        // Creating objects explicitly
        for (int i = 0; i < array.length; i++) {
            array[i] = new A();
            array[i].setA(i);
        }

        for (int i = 0; i < array.length; i++) {
            System.out.println("Object of A: " + array[i].getA());
        }
    }
}

/*
Key Notes
---------
Example:
String[] str = new String[3];

This creates only references.

Actual objects must be assigned:

str[0] = new String("Hello");
str[1] = "World";

Default value of reference → null
 */