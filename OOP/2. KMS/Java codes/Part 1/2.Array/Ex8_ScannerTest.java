import java.util.Scanner;

public class Ex8_ScannerTest {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        // Read lines until input ends
        while (sc.hasNextLine()) {
            System.out.println(sc.nextLine());
        }
    }
}

/*
Key Notes
---------
Scanner class location:
java.util.Scanner

Common methods:
nextInt()
nextDouble()
nextFloat()
nextLine()

Input source:
System.in
*/