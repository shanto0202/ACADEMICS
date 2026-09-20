
import java.util.Vector;

public class Ex6_VectorDemo {

    public static void main(String args[]) {

        Vector<Integer> v = new Vector<>();

        System.out.println("Size: " + v.size());
        System.out.println("Capacity: " + v.capacity());

        v.addElement(1);
        v.addElement(2);
        v.addElement(3);
        v.addElement(4);
        v.addElement(5);

        System.out.println("First: " + v.firstElement());
        System.out.println("Last: " + v.lastElement());

        //v.add(3);
        if (v.contains(3)) {
            System.out.println("Contains 3");
        }

        v.remove(4);

        for (int i = 0; i < v.size(); i++) {
            System.out.println(v.elementAt(i));
        }
        //v.get(1);
        //v.set(1,5);
    }
}

/*
Key Notes:

1. Vector is synchronized → thread-safe.
2. Slower than ArrayList due to synchronization.
3. Capacity doubles automatically.
4. Legacy class (rarely used now).
5. elementAt() similar to get().
 */
