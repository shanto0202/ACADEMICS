
public class Ex5_WrapDemo {

    public static void main(String args[]) {

        // boxing
        Integer iOb = new Integer(100); 

        // unboxing
        int i = iOb.intValue();

        System.out.println(i + " " + iOb);
    }
}

/*
Key Notes:

1. Wrapper classes → object version of primitive types.
2. Integer, Double, Boolean etc.
3. Boxing → primitive → object.
4. Unboxing → object → primitive.
5. Required when working with collections.
*/
