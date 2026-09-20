// String Character Extraction Example

public class Ex2_Extraction {

    public static void main(String[] args) {

        String s = "Hello World";

        char c1 = s.charAt(6);
        System.out.println(c1); // W

        char c2[] = new char[5];
        c2[0] = 'p';

        s.getChars(0, 4, c2, 1); // s = source, c2 = destination
        System.out.println(c2); // pHell

    }
}

/*
Key Notes
---------
charAt(index) → returns character

getChars(start,end,array,offset)
copies characters to array.
*/
