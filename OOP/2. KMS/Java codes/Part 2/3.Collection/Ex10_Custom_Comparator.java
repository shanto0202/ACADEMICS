
import java.util.*;

class TestClass implements Comparable<TestClass> {

    private String name;
    private int id;

    TestClass(int id, String name) {
        this.id = id;
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public int getId() {
        return id;
    }

    @Override
    public int compareTo(TestClass o) {
        return this.name.compareTo(o.name);
    }
}

class TestClassComparator implements Comparator<TestClass> { //Tor kora lagbo

    @Override
    public int compare(TestClass o1, TestClass o2) {
        return o1.getId() - o2.getId();
    }
}

public class Ex10_Custom_Comparator {

    public static void printList(List<TestClass> al) {
        for (TestClass t : al) {
            System.out.println(t.getId() + ", " + t.getName());
        }
        System.out.println();
    }

    public static void main(String args[]) {

        List<TestClass> al = new ArrayList<>();

        al.add(new TestClass(1, "C"));
        al.add(new TestClass(3, "A"));
        al.add(new TestClass(2, "E"));

        printList(al);

        Collections.sort(al); // by name //comparable
        printList(al);

        Collections.sort(al, new TestClassComparator()); // by id //comparator
        printList(al);

        Collections.sort(al, (a, b) -> a.getName().compareTo(b.getName())); // lambda
        printList(al);
    }
}

/*
Key Notes:

1. Comparable → default sorting (compareTo).
2. Comparator → custom sorting logic.
3. Collections.sort():
   - uses Comparable by default
   - can use Comparator
4. Lambda → modern sorting approach.
5. Important for exam → difference between Comparable & Comparator.
*/
