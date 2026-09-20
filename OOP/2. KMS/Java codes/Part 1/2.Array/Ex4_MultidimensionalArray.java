// Multidimensional Arrays
// Java supports arrays of arrays.

public class Ex4_MultidimensionalArray {

    public static void main(String[] args) {

        // Rectangular 2D array
        int[][] b = new int[3][4];

        System.out.println("Rows: " + b.length);
        System.out.println("Columns: " + b[0].length);

        // Jagged array
        int[][] jagged = new int[2][];

        jagged[0] = new int[2];
        jagged[1] = new int[3];

        jagged[0][0] = 1;
        jagged[0][1] = 2;

        jagged[1][0] = 3;
        jagged[1][1] = 4;
        jagged[1][2] = 5;

        // Printing jagged array
        for (int i = 0; i < jagged.length; i++) {
            for (int j = 0; j < jagged[i].length; j++) {
                System.out.print(jagged[i][j] + " ");
            }
            System.out.println();
        }
    }
}

/*
Key Notes
---------
Rectangular array:
all rows same size

Jagged array:
rows may have different sizes

Example:
int[][] b = new int[3][4]

Length:
b.length → rows
b[i].length → columns
 */