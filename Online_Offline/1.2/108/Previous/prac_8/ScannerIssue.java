import java.util.Scanner;
public class ScannerIssue {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        // 1. Read the Age (Integer)
        System.out.print("Enter your age: ");
        int age = sc.nextInt();
        // Current Buffer: "25\n" -> nextInt takes "25". Leftover: "\n"
        // 2. THE FIX (Consume the newline)
        // If you comment out this line, the program will skip the name input!
        sc.nextLine();

        // 3. Read the Name (String)
        System.out.print("Enter your full name: ");
        String name = sc.nextLine();

        // 4. Print Result
        System.out.println("\n--- Student Info ---");
        System.out.println("Age: " + age);
        System.out.println("Name: " + name);
        sc.close();
    }
}