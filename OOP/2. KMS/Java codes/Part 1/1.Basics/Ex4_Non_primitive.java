//Object Reference Example

public class Ex4_Non_primitive {

    int L, W, H;

    Ex4_Non_primitive(int l, int w, int h) {
        L = l;
        W = w;
        H = h;
    }

    public static void main(String args[]) {

        Ex4_Non_primitive b1; // reference
        Ex4_Non_primitive b2;

        b1 = new Ex4_Non_primitive(8, 5, 7);

        b2 = b1; // both refer same object

        b1 = new Ex4_Non_primitive(3, 9, 2);

        b1 = b2;

    }

}

/*
Key Notes
---------
Non-primitive types:
Objects
Arrays

Objects stored by reference.

Reference behaves like pointer
but without pointer arithmetic.

null → reference to nothing.
 */
