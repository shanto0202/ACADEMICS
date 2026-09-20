//can not run this code, run Ex4_SamePackage

public class Ex2_Protection {

    int n = 1;
    private int nPrivate = 2;
    protected int nProtected = 3;
    public int nPublic = 4;

    public Ex2_Protection() {
        System.out.println("---Protection---");
        System.out.print(n + " ");
        System.out.print(nPrivate + " ");
        System.out.print(nProtected + " ");
        System.out.print(nPublic + " ");
        System.out.println();
    }
}

/*
Key Notes:

1. Demonstrates all access modifiers:
   - default → same package
   - private → only inside class
   - protected → same package + subclass
   - public → everywhere
 */
