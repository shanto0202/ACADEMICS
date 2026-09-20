// String Conversion Example

public class Ex6_Conversion {

    public static void main(String[] args) {

        int n = 123;
        //Integer p = 2;
        String s1 = Integer.toString(n); // object to string
        String s2 = String.valueOf(n); //
        Integer i = Integer.valueOf("123");
        String s3 = n + "";

        //System.out.println(p);
        System.out.println(s1);
        System.out.println(s2);
        System.out.println(s3);
        //System.out.println(i);

        String s = "1234";

        int x = Integer.parseInt(s); //string to int

        System.out.println(x);

    }
}

/*
Key Notes
---------
int → String
Integer.toString()
String.valueOf()

String → int
Integer.parseInt()
 */
