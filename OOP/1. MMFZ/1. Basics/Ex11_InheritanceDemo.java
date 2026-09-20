// Demonstrates inheritance in Java

// Base class (Superclass)
class Base {

    private int x;

    public void setX(int newX) {
        x = newX;
    }

    public int getX() {
        return x;
    }

    public void showX() {
        System.out.println("X = " + x);
    }
}

// Derived class (Subclass)
class Derived extends Base {

    private int y;

    public void setY(int newY) {
        y = newY;
    }

    public void showY() {
        System.out.println("Y = " + y + "  X= " + getX());
    }
}

public class Ex11_InheritanceDemo {

    public static void main(String[] args) {
        Derived obj = new Derived();

        obj.setX(10);   // inherited method from Base
        obj.setY(20);   // method of Derived

        obj.showX();
        obj.showY();
    }
}

/*
Key Notes:
1. Inheritance → one class acquires properties of another class.
2. Base = superclass, Derived = subclass.
3. "extends" keyword is used in Java.
4. Subclass can access public methods of superclass.
5. Enables code reuse and hierarchical structure.
*/
