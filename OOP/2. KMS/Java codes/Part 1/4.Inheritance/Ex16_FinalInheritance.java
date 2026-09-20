// Using final with inheritance

class A {

    final void f() {
        System.out.println("This is a final method.");
    }

}
// class B extends A {
//     void f() {                // ERROR
//         System.out.println("Illegal!");
//     }
// }

final class C {

    void show() {
        System.out.println("Final class method");
    }

}

final class D extends A {

}
// class D extends C { }   // ERROR: cannot inherit final class

public class Ex16_FinalInheritance {

    public static void main(String[] args) {

        A obj = new A();
        obj.f();

        C c = new C();
        c.show();
        D d = new D();
        d.f();

    }

}

/*
Key Notes
---------
final method
→ cannot be overridden.

final class
→ cannot be inherited.

Used to restrict modification.
 */
