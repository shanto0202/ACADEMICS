// Substring Example

public class Ex3_Substring {

    public static void main(String[] args) {

        String s = "Hello World";

        String s1 = s.substring(6);
        System.out.println(s1); // World

        String s2 = s.substring(2, 8);
        System.out.println(s2); // llo Wo

    }
}

/*
Key Notes
---------
substring(start)

substring(start,end)

end index is exclusive.
*/