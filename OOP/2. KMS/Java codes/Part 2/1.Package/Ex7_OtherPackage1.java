//package p3.p4;
//import p1.Ex2_Protection;

public class Ex7_OtherPackage1 extends Ex2_Protection {

    Ex7_OtherPackage1() {
        //outside of the package we can not access n
        System.out.println("---Protection3---");
        System.out.print(nProtected + " ");
        System.out.print(nPublic + " ");
        System.out.println();
    }
}

/*
Key Notes:

1. Same as inheritance example.
2. protected accessible.
 */
