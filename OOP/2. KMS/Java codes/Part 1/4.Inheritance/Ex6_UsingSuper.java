
// Using super to access superclass hidden members

class C {

    int i;

    C() {
        System.out.println("Inside C's constructor");
    }

    void show() {
        System.out.println("Inside superclass show()");
    }
}

class D extends C {

    int i; // this i hides the i in C

    D(int a, int b) {

        super.i = a; // i in C
        i = b;       // i in D

        System.out.println("Inside D's constructor");
    }

    void show() {

        System.out.println("i in superclass: " + super.i);
        System.out.println("i in subclass: " + i);

        super.show();
    }
}

public class Ex6_UsingSuper {

    public static void main(String[] args) {

        D subOb = new D(1, 2);

        subOb.show();
    }
}

/*
Key Notes
---------
If subclass and superclass contain same variable name,
the subclass variable hides the superclass variable.

super.variable
→ accesses superclass variable.

super.method()
→ calls superclass method.

Here:
C has i
D also has i

So,
super.i → i of C
i        → i of D
*/
