// Private Methods in Interface (Java 9)

interface MyIFPrivate {

    default String f1() {
        login();
        return "Hello";
    }

    default String f2() {
        login();
        return "World";
    }
//can be called by a dafault method or another private mehtod of the same interface

    private void login() {
        System.out.print("login ");
    }

}

class MyIFPrivateImp implements MyIFPrivate {

    // void login() {
    //     System.out.println("login from class.");
    // }
}

public class Ex10_PrivateInterfaceMethod {

    public static void main(String[] args) {

        MyIFPrivate ifp = new MyIFPrivateImp();

        System.out.println(ifp.f1());
        System.out.println(ifp.f2());
        //System.out.println(ifp.login());
        //ifp.login();

        //MyIFPrivateImp ifp1 = new MyIFPrivateImp();
        //ifp1.login();
    }
}

/*
Key Notes
---------
Private methods added
in Java 9.

Used inside interface
to reuse code.
 */
