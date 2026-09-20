// Method Overriding Example

class Base {

    int a;

    Base(int a) {
        this.a = a;
    }

    void show() {
        System.out.println(a);
    }
}

class Child extends Base {

    int b;

    Child(int a, int b) {
        super(a);
        this.b = b;
    }

    @Override
    void show() {
        System.out.println(a + ", " + b);
    }
}

public class Ex9_MethodOverride {

    public static void main(String[] args) {

        Child o = new Child(10, 20);
        o.show();

        Base b = o;
        b.show(); // dynamic dispatch

    }
}

/*
Key Notes
---------
Method overriding occurs when subclass
provides new implementation of superclass method.

Runtime polymorphism occurs.
 */
