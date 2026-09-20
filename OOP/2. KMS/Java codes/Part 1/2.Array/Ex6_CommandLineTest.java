// Command-Line Arguments Example
// Run program as:
// java Ex6_CommandLineTest Hello 2 You
// Words after class name are passed to main() as String arguments.

public class Ex6_CommandLineTest {

    public static void main(String[] args) {

        // args is a String array containing command-line arguments
        System.out.println(args.length); // number of arguments

        for (int i = 0; i < args.length; i++) {
            System.out.println(args[i]); // print each argument
        }

    }
}

/*
Key Notes
---------
Command format:
java ClassName arg1 arg2 ... argN

Arguments are stored in:
String args[]

Number of arguments:
args.length

Example run:
java Ex5_CommandLineTest Hello 2 You

Output:
3
Hello
2
You
*/