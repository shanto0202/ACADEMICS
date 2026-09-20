// For-Each Loop Example
// Used to iterate arrays and collections.

public class Ex5_ForEachTest {

    public static void main(String[] args) {

        int numbers[] = {1, 2, 3, 4, 5};

        for (int x : numbers) {
            System.out.print(x + " ");
            x = x * 10; // does not change original array
        }

        System.out.println();

        int numbers2[][] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        for (int[] x : numbers2) {
            for (int y : x) {
                System.out.print(y + " ");
            }
            System.out.println();
        }
    }
}

/*
Key Notes
---------
Syntax:
for(type var : array)

Loop variable is copy of element.
Changing it does NOT change array value.
 */