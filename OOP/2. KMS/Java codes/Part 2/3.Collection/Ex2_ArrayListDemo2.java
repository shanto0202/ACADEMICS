
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Ex2_ArrayListDemo2 {

    public static void main(String args[]) {

        List<Integer> al = new ArrayList<>();

        System.out.println("Initial size: " + al.size());

        // add elements
        al.add(10);
        al.add(20);
        al.add(30);
        al.add(40);
        al.add(50);

        // foreach loop
        for (Integer i : al) {
            System.out.print(i + " ");
        }

        System.out.println();

        // lambda iteration
        al.forEach(x -> System.out.print(x + " "));

        System.out.println();

        al.remove(2); // remove index

        // convert to array
        Integer[] ia = new Integer[al.size()];
        al.toArray(ia); //List to array al->ia

        for (int i = 0; i < ia.length; i++) {
            System.out.print(ia[i] + " ");
        }

        System.out.println();
        // array to list
        List<Integer> alist = Arrays.asList(ia); //Array to List ia->alist

        for (Integer i : alist) {
            System.out.print(i + " ");
        }
    }
}

/*
Key Notes:

1. Enhanced for-loop → simple iteration.
2. forEach() with lambda → modern Java.
3. toArray() → List → Array conversion.
4. Arrays.asList() → Array → List conversion.
5. remove(index) removes element at that position.
6. Demonstrates interoperability between List and Array.
 */
