public class CommandLineTest {
    public static void main(String[] args) {
        // 1. Print how many arguments were passed
        // (In C++, this is like printing 'argc')
        System.out.println("Number of arguments: " + args.length);

        // 2. Loop through and print each argument
        for (int i = 0; i < args.length; i++) {
            System.out.println("Argument " + i + ": " + args[i]);
        }
    }
}
//javac CommandLineTest.java
//javac CommandLineTest.java