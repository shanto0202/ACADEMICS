// throw example

public class Ex7_Throw {

    public static void f() {

        try {
            throw new NullPointerException("f");
        }

        catch(NullPointerException e) {
            System.out.println("Inside catch of f()");
            throw e; // rethrow
        }

    }

    public static void main(String args[]) {

        try {
            f();
        }

        catch(NullPointerException e) {
            System.out.println("Inside catch of main()");
        }

    }
}

/*
Key Notes
---------
throw keyword manually
throws an exception.
*/
