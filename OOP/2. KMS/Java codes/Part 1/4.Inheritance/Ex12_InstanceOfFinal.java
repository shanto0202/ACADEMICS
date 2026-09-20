// instanceof and final example

class Animal {
}

class Dog extends Animal {
}

final class FinalClass {

    void f() {
        System.out.println("This is a final method.");
    }
}

public class Ex12_InstanceOfFinal {

    public static void main(String[] args) {

        String s = "Hello";

        System.out.println(s instanceof String);
        System.out.println(s instanceof Object);

        Animal a = new Dog();
        Animal b = new Animal();

        System.out.println(a instanceof Animal);
        System.out.println(a instanceof Dog);
        System.out.println(b instanceof Dog);

    }
}

/*
Key Notes
---------
instanceof → checks object type at runtime.

final method → cannot be overridden.

final class → cannot be inherited.
 */
