// Demonstration of Constructor Overloading in Java with Array of Objects

class MyClass {

    private int x;

    // Default constructor
    MyClass() {
        x = 0;
    }

    // Parameterized constructor
    MyClass(int n) {
        x = n;
    }

    public int getX() {
        return x;
    }
}

public class Ex2_constructor_overloading {

    public static void main(String[] args) {
        MyClass[] ob = new MyClass[5];   // array of object references

        for (int i = 0; i < ob.length; ++i) {
            if (i % 2 != 0) {
                ob[i] = new MyClass();      // default constructor
            } else {
                ob[i] = new MyClass(i + 1);   // parameterized constructor
            }
        }

        for (int i = 0; i < ob.length; ++i) {
            System.out.print(ob[i].getX() + " ");
        }
    }
}

/*
Key Notes:
1. Constructor Overloading → multiple constructors with different parameters.
2. Default constructor → no arguments.
3. Parameterized constructor → initializes object with specific values.
4. In Java, an array of objects stores references, not actual objects.
5. Each element must be initialized using 'new'.
 */
