
class A {

    public interface Nested {

        public boolean isNegative(int x);
    }
}

interface inNested extends A.Nested {

    public void print(String str);
}

class B implements inNested, A.Nested {

    public boolean isNegative(int x) {
        return x < 0 ? true : false;
    }

    public void print(String str) {
        System.out.println(str);
    }
}

public class Ex14_nested_interface {

    public static void main(String[] args) {
        A.Nested nes = new B();
        inNested ines = new B();
        B nes2 = new B();

        if (!nes.isNegative(10)) {
            ((B) nes).print("Positive");
        }

        if (!nes2.isNegative(10)) {
            (nes2).print("Positive");
        }

        if (ines.isNegative(-5)) {
            ((B) ines).print("Negative.");
        }
    }
}

/*
Key Notes:

1. Nested interface is declared inside class A.

2. Outside access uses fully qualified name A.Nested.

3. B implements both interfaces.

4. Casting is used to call methods not present in reference type.
 */
