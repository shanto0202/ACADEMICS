
enum Apple2 {
    Jonathan, GoldenDel, RedDel, Winesap, Cortland
}

public class Ex2_EnumDemo2 {

    public static void main(String args[]) {

        Apple2 ap;

        System.out.println("All Apple constants:");

        // values()
        Apple2 all[] = Apple2.values();

        for (Apple2 a : all) {
            System.out.println(a);
        }

        System.out.println();

        // valueOf()
        ap = Apple2.valueOf("Winesap");

        System.out.println("ap contains " + ap);
    }
}

/*
Key Notes:

1. values() → returns array of all enum constants.
2. valueOf(String) → converts string → enum.
3. Useful for iteration and dynamic usage.
4. Common viva question → these two methods.
*/
