//package p3.p4;
//import p1.Ex2_Protection;

public class Ex8_OtherPackage2 {

    Ex8_OtherPackage2() {
        System.out.println("---OtherPackage---");
        Ex2_Protection p = new Ex2_Protection();

        //System.out.println(p.n); // can not access from different package
        //System.out.println(p.nProtected); // can not access from different package, different non sub class
        System.out.println(p.nPublic);
    }

    public static void main(String[] args) {
        new Ex7_OtherPackage1();
        new Ex8_OtherPackage2();
    }
}

/*
Key Notes:

1. No package → everything is same scope.
2. All except private accessible.
 */
