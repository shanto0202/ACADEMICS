//package p2;
//import p1.Ex2_Protection;

public class Ex6_OtherPackage {

    Ex6_OtherPackage() {
        System.out.println("---OtherPackage---");
        Ex2_Protection p = new Ex2_Protection();

        System.out.print(p.n + " ");
        System.out.print(p.nProtected + " ");
        System.out.print(p.nPublic + " ");
        System.out.println();
    }

    public static void main(String[] args) {
        new Ex5_Protection2();
        new Ex6_OtherPackage();
    }
}

/*
Key Notes:

1. Since no package → behaves same package.
2. default and protected now accessible.
3. private still restricted.
*/
