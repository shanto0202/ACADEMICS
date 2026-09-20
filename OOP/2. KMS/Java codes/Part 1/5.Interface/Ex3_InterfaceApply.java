// Applying Interfaces

interface MyInterface {
//    default void print(String msg){
//     System.out.println("Atik");
//    }

    void print(String msg);
}

class MyClass1 implements MyInterface {

    public void print(String msg) {
        System.out.println(msg + " : " + msg.length());
    }
}

class MyClass2 implements MyInterface {

    public void print(String msg) {
        System.out.println(msg.length() + " : " + msg);
    }
}

public class Ex3_InterfaceApply {

    public static void main(String[] args) {

        MyClass1 mc1 = new MyClass1();
        MyClass2 mc2 = new MyClass2();
        //mc1.print("totoro");

        MyInterface mi;

        mi = mc1;
        mi.print("Hello World");

        mi = mc2;
        mi.print("Hello World");

    }
}

/*
Key Notes
---------
Interface reference enables
runtime polymorphism.
 */
