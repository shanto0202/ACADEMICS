// Dynamic Method Dispatch Example

class P {
    void call() {
        System.out.println("Inside P's call method");
    }
}

class Q extends P {
    void call() {
        System.out.println("Inside Q's call method");
    }
}

class R extends Q {
    void call() {
        System.out.println("Inside R's call method");
    }
}

public class Ex10_DynamicDispatch {

    public static void main(String[] args) {

        P p = new P();
        Q q = new Q();
        R r = new R();

        P x;

        x = p;
        x.call(); 

        x = q;
        x.call();

        x = r;
        x.call();

    }
}

/*
Key Notes
---------
Superclass reference decides
which object to refer to.

Method executed depends on object type
at runtime.
*/
