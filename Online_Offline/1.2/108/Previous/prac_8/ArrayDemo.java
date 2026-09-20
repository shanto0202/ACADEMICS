public class ArrayDemo {
    public static void main(String[] args) {
        int[] a = new int[10];
        for (int i = 0; i < a.length; i++) {
            a[i] = i;
        }
        // 3. Printing the array
        System.out.println("--- Printing Array 'a' ---");
        for (int i = 0; i < a.length; i++) {
            System.out.println("Element at index " + i + ": " + a[i]);
        }
        // --- PART 2: The Tricky Syntax (Slide 1) ---
        System.out.println("\n--- Variable Type Demo ---");
        // Case A: C-style declaration
        // 'c' is an array, 'x' is just an int
        int c[], x;
        c = new int[5]; // OK
        x = 10;         // OK
        // x = new int[5]; // ERROR! x is just a number.
        System.out.println("x is just a number: " + x);
        // Case B: Java-style declaration (Preferred)
        // The type is "int[]" (Integer Array). This applies to BOTH variables.
        int[] d, y;
        d = new int[5]; // OK
        y = new int[5]; // OK! y is ALSO an array.

        System.out.println("y is an array of length: " + y.length);
    }
}
