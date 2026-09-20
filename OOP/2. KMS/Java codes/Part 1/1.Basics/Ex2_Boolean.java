
public class Ex2_Boolean {

    public static void main(String args[]) {

        int a = 10;

        if (a > 0) // boolean expression required
        {
            System.out.println("Inside If");
        }

        boolean b = false;

        if (b) {
            System.out.println("Inside If");
        } else {
            System.out.println("Inside Else");
        }

    }
}

/*
Key Notes
---------
Java does NOT allow:

if(a) ❌

Must use boolean expression:

if(a > 0) ✔
 */