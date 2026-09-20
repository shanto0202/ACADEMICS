import java.util.HashMap;
import java.util.Objects;
// Custom class
class Point {
    int x, y;
    // Constructor
    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    // Override equals() to compare content
    @Override
    public boolean equals(Object o) {
        // Same reference → true
        if (o == this) {
            return true;
        }
        // If not same class → false
        if (!(o instanceof Point)) {
            return false;
        }
        // Typecast
        Point p = (Point) o;
        // Compare values
        return p.x == this.x && p.y == this.y;
    }

    // Override hashCode() to match equals()
    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }
}

public class Ex9_EqualsHashCodeDemo {

    public static void main(String[] args) {

        Point p1 = new Point(10, 20);
        Point p2 = new Point(10, 20);

        // equals() checks content
        System.out.println(p1.equals(p2)); // true

        // == checks reference
        System.out.println(p1 == p2); // false

        // HashMap usage
        HashMap<Point, String> m = new HashMap<>();

        m.put(p1, "Hello");

        // Works because equals + hashCode overridden
        System.out.println(m.get(p2)); // Hello
    }
}

/*
Key Notes:

1. == vs equals():

   - == → compares reference (same object or not)
   - equals() → compares content (if overridden)

2. Default behavior:
   - Object class equals() behaves like ==
   - so by default it compares references

3. String class overrides equals():
   - compares content instead of reference

4. For custom classes (like Point):
   if you want objects with same data to be equal,
   you MUST override:
   - equals()
   - hashCode()

5. equals() rules:
   - reflexive → x.equals(x)
   - symmetric → x.equals(y) == y.equals(x)
   - transitive

6. hashCode():
   - must return same value for equal objects
   - used in HashMap, HashSet

7. Why both needed?
   - HashMap first uses hashCode()
   - then uses equals() to confirm match

8. Important example:
   p1 and p2 have same values:
   - equals() → true
   - == → false

9. Without overriding hashCode():
   - HashMap may fail to retrieve value

10. Very important exam concept:
    "If equals() is overridden → hashCode() must also be overridden"

11. Slide concept summary:
    - == → reference comparison
    - equals() → can be overridden for content
    - hashCode() → required for hashing structures
 */
