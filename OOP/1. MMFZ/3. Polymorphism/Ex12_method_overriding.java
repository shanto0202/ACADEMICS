abstract class Figure {

    double dim1, dim2;

    // constructor
    Figure(double a, double b){
        dim1 = a;
        dim2 = b;
    }

    // abstract method
    abstract double area();

    // normal method
    void show(){
        System.out.println("Abstract");
    }
}

class Rectangle extends Figure {

    Rectangle(double a, double b){
        super(a, b);   // calling base class constructor
    }

    // method overriding
    double area(){
        return dim1 * dim2;
    }

    void show(){
        System.out.println("Rectangle Area: " + area());
    }
}


class Triangle extends Figure {

    Triangle(double a, double b){
        super(a, b);
    }

    // method overriding
    double area(){
        return 0.5 * dim1 * dim2;
    }

    void show(){
        System.out.println("Triangle Area: " + area());
    }
}


public class Ex12_method_overriding {

    public static void main(String[] args) {

        Rectangle r = new Rectangle(4,5);
        Triangle t = new Triangle(4,3);

        Figure figref;

        figref = r;
        figref.show();

        figref = t;
        figref.show();
    }
}

/*
Output
Rectangle Area: 20.0
Triangle Area: 6.0


Key Notes:

1. Method overriding occurs when a subclass redefines a method of the superclass.

2. The parent class method must be inherited and have the same signature.

3. Abstract classes can contain abstract methods (no body).

4. 'super()' calls the constructor of the parent class.

5. Runtime polymorphism occurs when a parent reference
   points to different subclass objects.
*/