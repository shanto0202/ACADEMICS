public class ArrayDemo3 {
    public static void main(String[] args) {
        // --- Part 1: 1D Array & The "Read-Only" Trap ---
        System.out.println("--- 1D Array Demo ---");
        int[] numbers = {1, 2, 3, 4, 5};
        // "for every integer 'x' inside 'numbers'..."
        for (int x : numbers) {
            System.out.print(x + " ");
            // TRAP: This creates a COPY of the value.
            // Modifying 'x' does NOT change the actual array!
            x = x * 10;
        }
        System.out.println(); // New line
        // Let's prove the array didn't change
        System.out.print("Original array after loop: ");
        for (int n : numbers) {
            System.out.print(n + " "); // Still 1, 2, 3...
        }
        System.out.println("\n");
        // --- Part 2: 2D Arrays (Arrays of Arrays) ---
        System.out.println("--- 2D Array Demo ---");
        // In Java, a 2D array is really an "Array of Arrays"
        int[][] numbers2 = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        // Outer loop gets each ROW (which is an int[] array)
        for (int[] row : numbers2) {

            // Inner loop gets each NUMBER in that row
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println(); // New line after each row
        }
    }
}