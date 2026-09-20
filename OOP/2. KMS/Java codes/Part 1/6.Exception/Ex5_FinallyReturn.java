// finally execution even with return

public class Ex5_FinallyReturn {

    public static void main(String args[]) {

        int a = 10, b = 0, c;

        try {
            c = a / b;
            System.out.println("This will never print");
        }

        catch(Exception e) {
            System.out.println("In Catch");
            System.out.println(e);
            return;
        }

        finally {
            System.out.println("In Finally");
        }

    }
}

/*
Key Notes
---------
finally executes
even if return occurs.
*/
