//package p2;
//import p1.Ex2_Protection;

public class Ex5_Protection2 extends Ex2_Protection {

    Ex5_Protection2() {
        System.out.println("---Protection2---");
        System.out.print(n + " "); // works now (same folder)
        System.out.print(nProtected + " ");
        System.out.print(nPublic + " ");
        System.out.println();
    }
}

/*
Key Notes:

1. No package → everything behaves as SAME PACKAGE.
2. default + protected + public accessible.
3. private still not accessible.
 */
