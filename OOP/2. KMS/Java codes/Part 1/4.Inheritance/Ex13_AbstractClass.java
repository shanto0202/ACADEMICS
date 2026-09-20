// Abstract Class Example

abstract class S {

    abstract void call();

    void call2() {
        System.out.println("This is a concrete method");
    }
}

class T extends S {

    void call() {
        System.out.println("T's implementation of call");
    }
}

public class Ex13_AbstractClass {

    public static void main(String args[]) {
        //S s = newS(); //abstract class can not be instantiated
        T t = new T();
        t.call();
        t.call2();

    }
}

/*
Key Notes
---------
Abstract classes cannot be instantiated.

Subclass must implement abstract methods.
 */
