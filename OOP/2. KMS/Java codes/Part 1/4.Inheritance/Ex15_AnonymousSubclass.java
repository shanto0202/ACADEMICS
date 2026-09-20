// Anonymous Subclass Example

abstract class S {

    // abstract method
    abstract void call();

    // concrete method allowed in abstract class
    void call2() {
        System.out.println("This is a concrete method");
    }
}

public class Ex15_AnonymousSubclass {

    public static void main(String args[]) {

        // cannot instantiate abstract class directly
        // S s = new S();  // illegal
        // anonymous subclass of S
        S s = new S() {
            void call() {
                System.out.println("Call method of an abstract class");
            }
        }; //As we don't have any child class here that's why we bcreated an anonymous subclass
        s.call();
        s.call2();

    }

}

/*
Key Notes
---------
Anonymous subclass:
new SuperClass(){ ... }

Used when subclass is needed once.

Commonly used with abstract classes
and interfaces.
 */
