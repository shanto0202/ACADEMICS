
import java.util.*;

class Employee implements Comparable<Employee> {

    int id, age;
    String name;

    Employee(int id, String name, int age) {
        this.id = id;
        this.name = name;
        this.age = age;
    }

    // getters
    String getName() {
        return name;
    }

    int getAge() {
        return age;
    }

    public int compareTo(Employee o) {
        if (age != o.age) {
            return age - o.age;
        }
        return name.compareTo(o.name);
    }
}

public class Ex12 {

    public static void main(String[] args) {

        List<Employee> list = new ArrayList<>();

        list.add(new Employee(1, "Rodgers", 10));
        list.add(new Employee(2, "Bradley", 25));
        list.add(new Employee(3, "Chambers", 15));
        list.add(new Employee(4, "Calvin", 10));
        list.add(new Employee(5, "Quinn", 30));
        list.add(new Employee(6, "Mccoy", 15));

        // Part (ii) stream
        List<String> names = list.stream()
                .map(Employee::getName)
                .toList();

        List<Employee> employees = list.stream()
                .filter(e -> e.getAge() <= 20)
                .toList();

        System.out.println(names);
        System.out.println(employees);

        // sorting
        Collections.sort(list);

        for (Employee e : list) {
            System.out.println(e.id + " " + e.name + " " + e.age);
        }
    }
}

/*
Key Notes:

1. Must declare:
   List<String> names
   List<Employee> employees

2. Stream:
   map → extract name
   filter → condition (age <= 20)

3. Getter required for method reference

4. Sorting:
   Comparable used (age → name)
*/
