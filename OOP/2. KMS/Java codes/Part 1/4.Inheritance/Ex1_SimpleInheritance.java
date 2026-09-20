// Simple Inheritance Example

class A {

    int i, j;

    void showij() {
        System.out.println(i + " " + j);
    }
}

class B extends A {

    int k;
    void showk() {
        System.out.println(k);
    }

    void sum() {
        System.out.println(i + j + k);
    }
}

public class Ex1_SimpleInheritance {

    public static void main(String[] args) {

        A superOb = new A();
        superOb.i = 10;
        superOb.j = 20;
        superOb.showij(); //10 20

        B subOb = new B();
        subOb.i = 7;
        subOb.j = 8;
        subOb.k = 9;

        subOb.showij();
        subOb.showk();
        subOb.sum();

    }
}

/*
Key Notes
---------
Inheritance uses keyword: extends

Superclass → A
Subclass → B

Subclass inherits members of superclass.
 */