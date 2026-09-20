
class X {

    void f1() {
        System.out.println("In f1");
    }
}

interface Y {

    void f2();
}

interface Z {

    void f3();
}

class MyX extends X implements Y, Z {

    public void f2() {
        System.out.println("In f2");
    }

    public void f3() {
        System.out.println("In f3");
    }
}

public class Ex4_BoundedGenerics<T extends X & Y & Z> {

    private T a;

    public void setObj(T a) {
        this.a = a;
    }

    public T getObj() {
        return a;
    }

    public static void main(String[] args) {
        MyX obj = new MyX();

        Ex4_BoundedGenerics<MyX> g = new Ex4_BoundedGenerics<>();
        g.setObj(obj);

        g.getObj().f1();
        g.getObj().f2();
        g.getObj().f3();
    }
}

/*
Key Notes:

1. Bounded generics → T extends X & Y & Z.
2. T must:
   - extend class X
   - implement interfaces Y and Z.
3. Ensures methods f1(), f2(), f3() are available.
4. Provides strong compile-time constraints.
*/
