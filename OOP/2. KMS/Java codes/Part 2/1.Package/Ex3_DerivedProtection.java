//can not run this code, run Ex4_SamePackage

public class Ex3_DerivedProtection extends Ex2_Protection {

    Ex3_DerivedProtection() {
        System.out.println("---DerivedProtection---");
        System.out.print(n + " ");
        // System.out.println(nPrivate); ❌
        System.out.print(nProtected + " ");
        System.out.print(nPublic + " ");
        System.out.println();
    }
}

/*
Key Notes:

1. Inheritance using extends.
2. private not accessible.
3. protected accessible.
 */
