// 1. You MUST import this package to use Scanner
import java.util.Scanner;
public class ScannerTest {
    public static void main(String[] args) {
        // 2. Create a Scanner object connected to the keyboard (System.in)
        // In C++, 'cin' exists automatically. In Java, you have to create it.
        Scanner scn = new Scanner(System.in);
        System.out.println("Type some numbers, pressing Enter after each one.");
        System.out.println("Type a non-number (like 'end') or press Ctrl+Z to stop.");
        // 3. The "Read until End-of-File" Loop
        // This checks: "Is the next thing in the buffer an Integer?"
        // Equivalent to C++: while (cin >> x)
        while (scn.hasNextInt()) {
            int x = scn.nextInt(); // Read the integer
            System.out.println("Output: " + x);
        }
        System.out.println("--- Done reading integers ---");
        scn.close();
    }
}
