
import java.util.ArrayList;
import java.util.List;

class MyClass {

    private int id;
    private String name;

    MyClass(int id, String name) {
        this.id = id;
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }
}

public class Ex3_ArrayListDemo3 {

    public static void main(String args[]) {

        List<MyClass> al = new ArrayList<>();

        System.out.println("Initial size: " + al.size());

        al.add(new MyClass(1, "Rodgers"));
        al.add(new MyClass(2, "Bradley"));
        al.add(new MyClass(3, "Chambers"));
        al.add(new MyClass(4, "Calvin"));
        al.add(new MyClass(5, "Quinn"));
        al.add(new MyClass(6, "Mccoy"));

        System.out.println("Size after additions: " + al.size());

        for (int i = 0; i < al.size(); i++) {
            MyClass mc = al.get(i);
            System.out.println(mc.getId() + ", " + mc.getName());
        }
    }
}

/*
Key Notes:

1. ArrayList can store objects (custom class).
2. Generics ensure type safety → List<MyClass>.
3. Encapsulation used → private variables + getters.
4. Access object data using methods.
5. Real-world usage → storing structured data.
*/