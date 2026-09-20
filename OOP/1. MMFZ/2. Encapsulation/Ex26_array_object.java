// Demonstration of Array of Objects in Java

class Samp {

    private int a;

    Samp(int n) {
        a = n;
    }

    public int getA() {
        return a;
    }
}

class Std {

    String name;
    int id;

    Std(String n, int i) {
        name = n;
        id = i;
    }

    public void show() {
        System.out.println(name + ":" + id);
    }
}

public class Ex26_array_object {

    public static void main(String[] args) {
        int[] A = new int[4];
        int[][] B = {{11, 12, 13, 14}};
        int[][] C = {{21, 22}, {23, 24}, {25, 26}};
        Samp[] S = new Samp[4];
        Std[] std = {new Std("J", 101), new Std("L", 102), new Std("H", 103)};

        for (int i = 0; i < 4; ++i) {
            A[i] = 30 + i;
            S[i] = new Samp(40 + i);
        }

        for (int i = 0; i < S.length; ++i) {
            System.out.print(S[i].getA() + " ");
        }

        System.out.println();

        for (Std s : std) {
            System.out.println(s.name + ":" + s.id);
        }
    }
}

/*
Key Notes:
1. Array of objects → stores multiple objects of the same class.
2. Syntax: ClassName[] arr = new ClassName[size];
3. Each element must be initialized using 'new'.
4. Objects are accessed using array indexing (arr[i].method()).
5. Enhanced for-loop (for-each) can iterate through object arrays.
 */
