
import java.io.Console;

public class Ex15_ConsoleDemo {

    public static void main(String args[]) {

        Console con = System.console();

        if (con == null) {
            return;
        }

        String userName = con.readLine("Enter Username:");
        char[] p = con.readPassword("Enter Password:");

        String password = new String(p);

        con.printf("UserName:%s\n", userName);
        con.printf("Password:%s\n", password);
    }
}

/*
Key Notes:

1. Console → user input/output (secure).
2. readPassword() → hides input.
3. Works only in real console (not IDE sometimes).
4. printf() → formatted output.
*/
