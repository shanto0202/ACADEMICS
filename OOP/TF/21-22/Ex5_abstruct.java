interface x1 {
    void f1();
    static void f2() {}
    default void f3() {}
}

interface x2 {
    void f4();
    private void f5() {}
}

abstract class A implements x1 {
    final void f6() {}
    abstract void f7();
}

public class Ex5_abstruct extends A implements x2 {
    public void f1() {}
    public void f4() {}
    void f7() {}
}