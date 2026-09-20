// Issue with Scanner when mixing nextInt() and nextLine()

import java.util.Scanner;

public class Ex7_ScannerIssue {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int age = sc.nextInt();

        sc.nextLine(); // consume leftover newline

        String name = sc.nextLine();

        System.out.println(age);
        System.out.println(name);

    }

}

/*
Key Notes
---------
Problem:
nextInt() does not consume newline.

So nextLine() reads empty string.

Solution:
Call nextLine() once to consume newline.

Example fix:

int age = sc.nextInt();
sc.nextLine(); // consume newline
String name = sc.nextLine();
*/