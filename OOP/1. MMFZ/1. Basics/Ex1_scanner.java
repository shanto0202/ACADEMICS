import java.util.Scanner;

public class Ex1_scanner {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        // print() displays text WITHOUT moving to next line
        System.out.print("Enter the first number: ");
        // nextInt() reads an integer value from user
        int a = sc.nextInt();
        System.out.print("Enter the second number: ");
        int b = sc.nextInt();
        // Perform addition and store result
        int sum = a + b;
        System.out.println("The sum is " + sum + "."); // println for next line
        sc.close();
    }
}

//gci -r -filter *.class | rm