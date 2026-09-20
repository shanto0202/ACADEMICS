
import java.util.HashMap;
import java.util.Objects;

class Point {

    private int x, y;

    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public String toString() {
        return "(" + x + ", " + y + ")";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (!(o instanceof Point)) {
            return false;
        }
        Point p = (Point) o;
        return x == p.x && y == p.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }
}

class Circle {

    Point center;
    int radius;

    Circle(int x, int y, int r) {
        center = new Point(x, y);
        this.radius = r;
    }

    @Override
    public String toString() {
        return "Circle: center " + center + ", radius: " + radius;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (!(o instanceof Circle)) {
            return false;
        }
        Circle c = (Circle) o;
        return radius == c.radius && center.equals(c.center);
    }

    @Override
    public int hashCode() {
        return Objects.hash(center, radius);
    }
}

public class Ex6_Overridde {

    public static void main(String[] args) {
        Circle c1 = new Circle(10, 20, 5);
        Circle c2 = new Circle(10, 20, 5);

        System.out.println(c1);
        System.out.println(c2);
        System.out.println(c1.equals(c2));

        HashMap<Circle, String> m = new HashMap<>();
        m.put(c1, "I am a Circle");

        System.out.println(m.get(c2));
    }
}