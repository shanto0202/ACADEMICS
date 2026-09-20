// Nested Interface Example

class A {

    interface NestedIF {
        boolean isNonNegative(int x);
    }

}

class B implements A.NestedIF {

    public boolean isNonNegative(int x) {
        return x >= 0;
    }

}

public class Ex4_NestedInterface {

    public static void main(String[] args) {

        A.NestedIF nif = new B();
        B niF=new B();

        System.out.println(niF.isNonNegative(100));
        System.out.println(nif.isNonNegative(-10));
        System.out.println(niF.isNonNegative(-10));

    }
}

/*
Key Notes
---------
Interface inside class
is called nested interface.

Access using:
OuterClass.Interface
*/
