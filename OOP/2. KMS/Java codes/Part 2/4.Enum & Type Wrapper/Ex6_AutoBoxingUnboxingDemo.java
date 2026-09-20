
public class Ex6_AutoBoxingUnboxingDemo {

    static int m(Integer v) {
        return v; // auto-unbox
    }

    public static void main(String args[]) {

        Integer a = m(100); // autobox + unbox

        System.out.println(a);

        Integer iOb, iOb2;
        int i;

        iOb = 100; // autobox

        System.out.println("Original: " + iOb);

        ++iOb; // unbox → increment → rebox

        System.out.println("After ++: " + iOb);

        iOb2 = iOb + (iOb / 3);

        System.out.println("iOb2: " + iOb2);

        i = iOb + (iOb / 3);

        System.out.println("i: " + i);

        Integer intOb = 100;
        Double doubleOb = 98.6;

        doubleOb = doubleOb + intOb;

        System.out.println("doubleOb: " + doubleOb);
    }
}

/*
Key Notes:

1. Autoboxing → automatic conversion primitive → object.
   Example: Integer i = 100;

2. Auto-unboxing → object → primitive automatically.
   Example: int x = i;

3. No need for intValue() manually.

4. Expressions:
   - unbox → compute → rebox

5. Mixing types works due to auto conversion.

6. VERY IMPORTANT for interview & exam.
*/
