// Multiple catch clauses

public class Ex6_MultipleCatch {

    public static void main(String args[]) {

        int a = 10, b = 0, c = 0;

        try {
            c = a / b;
        }

        catch (ArithmeticException e1) {
            System.out.println(e1);
        }

        catch (NullPointerException e2) {
            System.out.println(e2);
        }

        catch (Exception e) {
            System.out.println(e);
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
Multiple catch blocks
handle different exceptions.
*/
