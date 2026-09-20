// try-catch-finally example

public class Ex2_CaughtException {

    public static void main(String args[]) {

        int a = 10, b = 0, c = 0;

        try {
            c = a / b;
            System.out.println("This will never print");
        }

        catch (Exception e) {
            System.out.println("In Catch");
            System.out.println(e.getMessage());
        }

        finally {
            System.out.println("In Finally");
        }

        System.out.println(a);
        System.out.println(b);
        System.out.println(c);

    }
}

/*
Key Notes
---------
try → risky code

catch → handles exception

finally → always executes
*/
