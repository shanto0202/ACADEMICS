
class Base {

    final private int x;
    final private int y;

    Base(int n, int p) {
        x = n;
        y = p;
        System.out.println("Constructing Base class.");
    }

    public void showXY() {
        System.out.println(x + " " + y);
    }
}

class Derived extends Base {

    final private int i;
    final private int j;

    Derived(int n, int m, int p) {
        super(n, p); // call base constructor
        i = n;
        j = m;
        System.out.println("Constructing Derived class.");
    }

    public void showIJ() {
        System.out.println(i + " " + j);
    }
}

public class Ex3_constructor_passing {

    public static void main(String[] args) {
        Derived ob = new Derived(10, 20, 30);
        ob.showXY();
        ob.showIJ();
    }
}

/*
Key Notes:

1. super(n, p) passes arguments to Base constructor.

2. Base constructor executes before Derived constructor.

3. final members are initialized in constructor.

4. Java has no destructor.
*/
