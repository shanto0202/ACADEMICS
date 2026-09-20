// Anonymous class implementing interface
interface Callback2 {
    void call(int param);
}

public class Ex2_AnonymousInterface {

    public static void main(String[] args) {
        Callback2 callback = new Callback2() {
            @Override
            public void call(int param) {
                System.out.println("call method called with " + param);
            }
        };

        callback.call(10);

    }
}

/*
Key Notes
---------
Anonymous class:
new Interface(){ ... }

Used for quick one-time implementation.
*/
