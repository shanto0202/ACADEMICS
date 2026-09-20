// Abstract Class Area Example

abstract class Figure2 {

    double d1, d2;

    Figure2(double a, double b) {
        d1 = a;
        d2 = b;
    }

    abstract double area();
}

class Rectangle2 extends Figure2 {

    Rectangle2(double a, double b) {
        super(a, b);
    }

    public double area() {
        System.out.println("Inside area for Rectangle");
        return d1 * d2;
    }
}

class Triangle2 extends Figure2 {

    Triangle2(double a, double b) {
        super(a, b);
    }

    public double area() {
        System.out.println("Inside area for Triangle");
        return (d1 * d2) / 2;
    }
}

public class Ex14_AbstractArea {

    public static void main(String[] args) {

        Rectangle2 r = new Rectangle2(9,5);
        Triangle2 t = new Triangle2(10,8);

        Figure2 ref;

        ref = r;
        System.out.println("Area: " + ref.area());

        ref = t;
        System.out.println("Area: " + ref.area());

    }
}

/*
Key Notes
---------
Abstract method must be implemented
in subclass.

Used for abstraction.
*/
