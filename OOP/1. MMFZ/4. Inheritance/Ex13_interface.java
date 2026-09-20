
interface InterfaceDemo {

    public double PI = 3.14159;

    public void volume();

    default double circleArea(double radius) { // default method
        System.out.println(getName());
        return PI * radius * radius;
    }

    private String getName() { // private interface method
        return "Area is calculated using default method.";
    }
}

class Cone implements InterfaceDemo {

    private String name;
    private double height;
    private double radius;

    Cone(double nh, double nr) {
        height = nh;
        radius = nr;
    }

    public void volume() {
        double vol = height * circleArea(radius) / 3;
        System.out.println(name + " Volume: " + vol);
    }
}

class Cylindar implements InterfaceDemo {

    private String name;
    private double height;
    private double radius;

    Cylindar(double nh, double nr) {
        height = nh;
        radius = nr;
    }

    public void volume() {
        double vol = height * circleArea(radius);
        print(vol);
    }

    private void print(double vol) {
        System.out.println(name + " Volume: " + vol);
    }
}

public class Ex13_interface {

    public static void main(String[] args) {
        Cylindar cylindar = new Cylindar(5.6, 4.2);
        Cone cone = new Cone(5.6, InterfaceDemo.PI);
        cylindar.volume();
        cone.volume();
    }
}

/*
Key Notes:

1. Interface can contain constants and abstract methods.

2. default method provides shared implementation.

3. private interface method supports internal reuse.

4. A class implements an interface using "implements".
*/
