// Demonstration of final keyword in Java

class Figure {
    //public static final int getValue() -->for function
    final private double pi = 3.14159;   // final variable (constant)
    private double radius;

    public void setRadius(double newRadius) {
        radius = newRadius;
    }

    // final method (cannot be overridden)
    final public double circleArea() {
        return pi * radius * radius;
    }
}

// final class (cannot be inherited)
final class Cylinder extends Figure {

    final private double height;
    Cylinder(double newRadius, double newHeight) {
        setRadius(newRadius);
        height = newHeight;
    }

    public double cylinderVolume() {
        return circleArea() * height;
    }
}

public class Ex24_final {
    public static void main(String[] args) {
        Cylinder cylinder = new Cylinder(3.0, 4.0);
        System.out.print(cylinder.cylinderVolume());
    }
}

/*
Key Notes:
1. final variable → constant; value cannot be changed after initialization.
2. final method → cannot be overridden in subclasses.
3. final class → cannot be extended (no inheritance).
4. final variables can be initialized when declared or inside constructor.
5. C++ does not have the same 'final' keyword concept as Java.
*/
