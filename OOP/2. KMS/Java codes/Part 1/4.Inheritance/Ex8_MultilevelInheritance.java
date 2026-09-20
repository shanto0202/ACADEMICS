// Multilevel Inheritance

class X {

    int a;

    X() {
        System.out.println("Inside X's constructor");
    }
    public void getX() {
        System.out.println(a);
    }
}

class Y extends X {

    int a;
    int b;

    Y() {
        System.out.println("Inside Y's constructor");
    }

    public void getY() {
        System.out.println(a+" "+b);
    }
}

class Z extends Y {

    int c;

    Z() {
        System.out.println("Inside Z's constructor");
    }
    public void getZ() {
        System.out.println(c);
    }
}

public class Ex8_MultilevelInheritance {

    public static void main(String[] args) {

        Z z = new Z();

        z.a = 10;
        z.b = 20;
        z.c = 30;
        z.getX();
        z.getY();
        z.getZ();
    }
}

/*
Key Notes
---------
Multilevel inheritance:
X → Y → Z

Constructors execute from superclass → subclass.
 */
