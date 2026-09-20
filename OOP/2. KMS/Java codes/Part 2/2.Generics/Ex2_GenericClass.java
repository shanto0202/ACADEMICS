
public class Ex2_GenericClass<T> {

    private T a;

    public void setObj(T a) {
        this.a = a;
    }

    public T getObj() {
        return this.a;
    }

    public static void main(String[] args) {
        Ex2_GenericClass<Integer> g1 = new Ex2_GenericClass<>();
        g1.setObj(10);

        Ex2_GenericClass<String> g2 = new Ex2_GenericClass<>();
        g2.setObj("Hello");
        //g2.setObj(10);

        System.out.println(g1.getObj());
        System.out.println(g2.getObj());
    }
}

/*
Key Notes:

1. T → type parameter (placeholder for actual type).
2. Provides compile-time type safety.
3. No casting required.
4. g1 → works with Integer, g2 → works with String.
5. Wrong type insertion (e.g., g2.setObj(10)) → compile-time error.
*/
