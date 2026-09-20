
public class Ex26_Auto_boxing {

    public static void main(String[] args) {

        // wrapper object creation
        Integer iob1 = Integer.valueOf(100);

        // auto-boxing (primitive → object)
        Integer iob2 = 150;

        // auto-unboxing (object → primitive)
        double num1 = iob1;

        int num2 = iob2.intValue();

        double sum1 = num1 + num2;

        // automatic unboxing during arithmetic
        int sum2 = iob1 + iob2;

        // convert object to double
        double num = iob1.doubleValue();

        System.out.println("Primitive Sum: " + sum1);
        System.out.println("Object sum: " + sum2);

        System.out.println("Primitive Sum: " + (num1 + num2));
        System.out.println("Object sum: " + (iob1 + iob2));

        System.out.println(num);
    }
}


/*
Key Notes:

1. Java does NOT support operator overloading like C++.

2. Wrapper classes convert primitive types into objects.
   Examples: Integer, Double, Float, Long, Character, Boolean.

3. Auto Boxing:
   primitive → object
   Example:
       Integer i = 10;

4. Auto Unboxing:
   object → primitive
   Example:
       int x = i;

5. valueOf()  → primitive to object conversion.
6. intValue(), doubleValue() → object to primitive conversion.

7. Arithmetic operations automatically unbox objects.
*/
