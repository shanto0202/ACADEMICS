
public class Ex3_MultipleGenerics<S, T> {

    private S a;
    private T b;

    public Ex3_MultipleGenerics(S a, T b) {
        this.a = a;
        this.b = b;
    }

    public S getFirst() {
        return a;
    }

    public T getSecond() {
        return b;
    }

    public static void main(String[] args) {
        Ex3_MultipleGenerics<Integer, String> obj = new Ex3_MultipleGenerics<>(10, "Hello");

        System.out.println(obj.getFirst());
        System.out.println(obj.getSecond());
    }
}

/*
Key Notes:

1. Multiple type parameters → <S, T>.
2. Allows storing two different types in one class.
3. S → Integer, T → String in this example.
4. Useful for pairs, maps, etc.
*/
