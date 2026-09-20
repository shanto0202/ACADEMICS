
import java.util.ArrayList;
import java.util.List;

public class Ex1_ArrayListDemo1 {

    public static void main(String args[]) {

        // create an array list
        List<String> al = new ArrayList<>(); // List->interface

        System.out.println("Initial size of al: " + al.size());

        // add elements
        al.add("C");
        al.add("A");
        al.add("E");
        al.add("F");
        al.add("D");
        al.add("F");
        
        al.set(1,"K"); //ifat!!!
        System.out.println("Size after additions: " + al.size());

        // display list
        System.out.println("Contents: " + al);

        for (int i = 0; i < al.size(); i++) {
            System.out.print(al.get(i) + " "); //v[i]
        }
        //String p = al.get(0);
        System.out.println();
        // remove elements
        al.remove("F");
        al.remove(2);

        System.out.println("Size after deletion: " + al.size());
        System.out.println("Contents: " + al);
    }
}

/*
Key Notes:
//Atik
1. ArrayList is dynamic → size can grow/shrink.
2. List<String> → type-safe due to generics.
3. add() → insert element.
4. remove():
   - remove("F") → remove by value
   - remove(2) → remove by index
5. get(i) → access element.
6. size() → returns number of elements.
7. Internally uses dynamic array → fast access.
 */
