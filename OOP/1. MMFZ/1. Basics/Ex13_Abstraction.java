// Demonstrates abstraction using abstract class and method overriding

abstract class Figure {

    double dim1, dim2;

    // Constructor
    Figure(double a, double b) {
        dim1 = a;
        dim2 = b;
    }

    // Abstract method
    abstract double area();

    // Normal method
    void show() {
        System.out.println("Abstract");
    }
}

// Rectangle class
class Rectangle extends Figure {

    Rectangle(double a, double b) {
        super(a, b);
    }

    double area() {
        return dim1 * dim2;
    }

    void show() {
        System.out.println("Rectangle Area: " + area());
    }
}

// Triangle class
class Triangle extends Figure {

    Triangle(double a, double b) {
        super(a, b);
    }

    double area() {
        return 0.5 * dim1 * dim2;
    }

    void show() {
        System.out.println("Triangle Area: " + area());
    }
}

public class Ex13_Abstraction {

    public static void main(String[] args) {

        Rectangle r = new Rectangle(10, 7);
        Triangle t = new Triangle(10, 5);

        Figure figref;

        figref = r;
        figref.show();

        figref = t;
        figref.show();
    }
}

/*
Key Notes:
1. abstract class → cannot create objects.
2. abstract method → must be overridden in subclasses.
3. "extends" used for inheritance.
4. "super()" calls parent constructor.
5. Demonstrates runtime polymorphism using base reference.
*/