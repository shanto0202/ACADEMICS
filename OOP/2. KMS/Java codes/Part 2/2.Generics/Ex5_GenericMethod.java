
class GenCons {

    double val;

    public <T extends Number> GenCons(T arg) {
        val = arg.doubleValue();
        // T val;
        // public GenCons(T arg) {
        //     val = arg;
    }

    void showVal() {
        System.out.println("val: " + val);
    }

    public static <V> boolean isIn(V x, V[] a) {
        for (V t : a) {
            if (t == x) {
                return true;
            }
        }
        return false;
    }
}

public class Ex5_GenericMethod {

    public static void main(String[] args) {
        GenCons obj1 = new GenCons(100);
        GenCons obj2 = new GenCons(123.5);

        obj1.showVal();
        obj2.showVal();

        Integer[] arr = {1, 2, 3};
        System.out.println(GenCons.isIn(1, arr));
    }
}

/*
Key Notes:

1. Generic constructor → <T extends Number>.
2. Accepts only Number types (Integer, Double, etc).
3. Generic method → <V> works independently of class.
4. isIn() checks element presence in array.
5. No casting required.
 */
