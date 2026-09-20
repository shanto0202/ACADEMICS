// Default Interface Method

interface MyIF {

    int getNumber();

    default String getString() {
        return "Default String";
    }

}

class MyIFImp implements MyIF {

    public int getNumber() {
        return 100;
    }

    // public String getString() {
    //     return "implemented";
    // }

}

public class Ex7_DefaultInterfaceMethod {

    public static void main(String[] args) {

        MyIFImp m = new MyIFImp();

        System.out.println(m.getNumber());
        System.out.println(m.getString());

    }
}

/*
Key Notes
---------
Default methods introduced
in Java 8.

Allows method implementation
inside interface.
 */
