// Uncaught Exception Example

public class Ex1_UncaughtException {

    public static void main(String args[]) {

        int a = 10, b = 0;

        int c = a / b;   // Arithmetic Exception

        System.out.println(a);
        System.out.println(b);
        System.out.println(c);

        String s = null;
        System.out.println(s.length()); // NullPointerException

    }
}

/*
Key Notes
---------
If exception is not handled,
program terminates.

Example:
ArithmeticException
NullPointerException
 */