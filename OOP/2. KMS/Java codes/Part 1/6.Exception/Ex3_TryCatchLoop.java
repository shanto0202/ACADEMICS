
import java.util.Random;

// try-catch inside loop
public class Ex3_TryCatchLoop {

    public static void main(String args[]) {

        int a = 10, b, c;
        Random r = new Random();

        for (int i = 1; i <= 5; i++)
            try {
            b = r.nextInt();
            c = r.nextInt();
            a = 12345 / (b / c);
        } catch (ArithmeticException e) {
            System.out.println(e.getMessage());
            a = 0;
        } finally {
            System.out.println(i + " : " + a);
        }

    }
}

/*
Key Notes
---------
try can appear inside loops.
Exceptions handled per iteration.
 */
