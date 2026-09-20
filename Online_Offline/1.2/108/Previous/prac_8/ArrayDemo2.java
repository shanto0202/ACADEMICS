class A {
    private int a;
    // Setter
    public void setA(int a) {
        this.a = a;
    }
    // Getter
    public int getA() {
        return a;
    }
}

// Main Class
public class ArrayDemo2 {
    public static void main(String[] args) {
        // 1. Create the Array of References
        // CRITICAL: This does NOT create 10 objects. 
        // It creates 10 "null" pointers capable of holding class A objects.
        A[] array = new A[10];

        System.out.println("Step 1: Array created. array[0] is currently: " + array[0]);

        // 2. Instantiate the Objects
        for (int i = 0; i < array.length; i++) {
            // You MUST do this step, otherwise array[i] is null!
            array[i] = new A();

            // Now we can use the object
            array[i].setA(i);
        }

        // 3. Print the values
        System.out.println("Step 2: Objects created and values set.");
        for (int i = 0; i < array.length; i++) {
            System.out.println("Object at index " + i + ": " + array[i].getA());
        }
    }
}
