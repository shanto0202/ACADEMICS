// Simple Interface Example

interface Callback {
    void call(int param);
}

class Client implements Callback {

    public void call(int p) {
        System.out.println("call method called with " + p);
    }
    public void f() {
        System.out.println("simple method, not related with Callback");
    }
}

public class Ex1_SimpleInterface {

    public static void main(String[] args) {

        Client client = new Client();
        client.call(42);
        client.f();
        Callback cb = new Client(); // interface reference
        cb.call(84);

        // cb.f(); // Error: not in interface
    }
}

/*
Key Notes
---------
Interface methods are implicitly:
public + abstract

Interface variables are:
public static final

Interface reference can refer to
objects of implementing classes.
*/