class MyClass {
    private int a = 0;
    MyClass() {
        System.out.println("No Argument Constructor");
    }
    MyClass(int newA) {
        System.out.println("Constructor with Argument");
        a = newA;
    }
    public void show() {
        System.out.println(a);
    }
}

public class Ex1_constructor {
    public static void main(String[] args) {
        MyClass ob1 = new MyClass();
        MyClass ob2 = new MyClass(10);
        ob1.show();
        ob2.show();
    }
}
