// String Concatenation and Search

public class Ex5_SearchConcat {

    public static void main(String[] args) {

        String s1 = new String("Happy ");
        String s2 = new String("Birthday");

        String s3 = s1.concat(s2);

        System.out.println(s3);

        String s = "Hello World";

        System.out.println(s.indexOf('o'));    //first o
        System.out.println(s.lastIndexOf('o')); //last o

    }
}

/*
Key Notes
---------
concat() → joins strings

indexOf(char)

lastIndexOf(char)
 */
