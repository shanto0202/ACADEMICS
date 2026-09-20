
class MyClass {

    private int a;

    MyClass() {
        System.out.println("In Constructor");
        a = 10;
    }

    public int getA() {
        return a;
    }
}

public class Ex7_Encapsulation {

    public static void main(String[] args) {
        MyClass ob = new MyClass();
        // System.out.println("a: " + a);  // Error
        System.out.println(ob.getA());
    }
}
