
abstract class Figure {

    double dim1, dim2;

    Figure(double a, double b) {
        dim1 = a;
        dim2 = b;
    }

    abstract double area(); // abstract method
}

class Rectangle extends Figure {

    Rectangle(double a, double b) {
        super(a, b);
    }

    double area() {
        return dim1 * dim2;
    }
}

class Triangle extends Figure {

    Triangle(double a, double b) {
        super(a, b);
    }

    double area() {
        return 0.5 * dim1 * dim2;
    }
}

public class Ex11_Abstruct_class {

    public static void main(String[] args) {
        Rectangle r = new Rectangle(4, 5);
        Triangle t = new Triangle(4, 3);
        Figure figref; //reference variable
        figref = r;
        System.out.println("Area: " + figref.area());
        figref = t;
        System.out.println("Area: " + figref.area());
    }
}

/*
Key Notes:

1. Figure is an abstract class.

2. area() must be overridden in subclasses.

3. Abstract class reference can refer to subclass object.

4. Demonstrates dynamic method dispatch.
 */
