
import java.util.Arrays;

public class Ex5_ArraysDemo {

    static void display(int array[]) {
        for (int i : array) {
            System.out.print(i + " ");
        }
        System.out.println();
    }

    public static void main(String args[]) {

        int[] array = new int[10];

        for (int i = 0; i < 10; i++) {
            array[i] = -3 * i;
        }

        System.out.print("Original: ");
        display(array);

        Arrays.sort(array);

        System.out.print("Sorted: ");
        display(array);

        Arrays.fill(array, 2, 6, -1); // 0 indexing

        System.out.print("After fill: ");
        display(array);

        Arrays.sort(array);

        System.out.print("Sorted again: ");
        display(array);

        int index = Arrays.binarySearch(array, -9);

        System.out.println("Index of -9: " + index);
    }

}

/*
Key Notes:

1. Arrays class provides utility functions.
2. sort() → sorting.
3. fill(start, end, value) → partial overwrite.
4. binarySearch() → must be sorted before use.
5. Useful for array manipulation in exams.
 */
