// String Split Example

public class Ex7_Split {

    public static void main(String[] args) {

        String test = "abc,j,def,123";

        String out[] = test.split(",");

        System.out.println(out.length);

        for (int i = 0; i < out.length; i++) {
            System.out.println(out[i]);
        }

    }
}

/*
Key Notes
---------
split(regex)

Returns String array.

Used to break strings into tokens.
*/
