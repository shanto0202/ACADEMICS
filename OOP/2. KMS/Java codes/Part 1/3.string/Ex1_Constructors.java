// String Constructors Example

public class Ex1_Constructors {

    public static void main(String[] args) {

        char charArray[] = {'b', 'i', 'r', 't', 'h', ' ', 'd', 'a', 'y'};
        byte byteArray[] = {(byte) 'n', (byte) 'e', (byte) 'w', (byte) ' ', (byte) 'y', (byte) 'e', (byte) 'a', (byte) 'r'};

        String s = new String("hello"); // hello
        String s1 = new String(); // empty string
        String s2 = new String(s); // copy constructor
        String s3 = new String(charArray); // birth day
        String s4 = new String(charArray, 6, 2); // day
        String s5 = new String(byteArray); // new year
        String s6 = "Wel" + "come"; // Welcome

        System.out.println(s);
        System.out.println(s1);
        System.out.println(s2);
        System.out.println(s3);
        System.out.println(s4);
        System.out.println(s5);
        System.out.println(s6);
    }
}

/*
Key Notes
---------
String class belongs to java.lang package.

Strings are immutable.

Constructors:
new String("text")
new String(char[])
new String(byte[])
*/
