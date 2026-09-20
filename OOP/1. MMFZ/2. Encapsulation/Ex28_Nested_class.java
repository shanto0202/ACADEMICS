// Demonstration of Nested Class in Java

class Outer {

    private int a;

    Outer(int x) {
        a = x;
    }

    public void show() {
        System.out.println("Outer: " + a);
    }

    public void showInner(int x) {
        Inner inner = new Inner(x);
        inner.show();
    }

    // Inner class
    public class Inner {

        private int b;
        Inner(int y) {
            b = y;
        }

        public void show() {
            System.out.println("Inner: " + b);
        }

        public void showOuter(Outer ob) {
            ob.show();
        }
    }

    // Another nested class
    public class Inner2 {

        public void show(String str) {
            System.out.println(str);
        }
    }

    Inner2 inner2 = new Inner2();
}

public class Ex28_Nested_class {

    public static void main(String[] args) {

        Outer outer = new Outer(10);

        outer.show();
        outer.showInner(20);

        Outer.Inner inner = outer.new Inner(30);
        inner.show();
        inner.showOuter(outer);

        outer.inner2.show("Hello from Inner2!");
    }
}

/*
Key Notes:
1. Nested class → a class declared inside another class.
2. Non-static nested class is called Inner Class.
3. Inner class can access members of the outer class.
4. Object creation: Outer.Inner obj = outer.new Inner(...).
5. Helps logically group related classes and improve encapsulation.
*/