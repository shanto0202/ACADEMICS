// Demonstration of static variable, static method and static block in Java

class StaticDemo {

    static int a = 3;
    static int b;
    static int c;

    // static method
    static void show(int x) {
        a++; //4
        b--; //11
        System.out.print("A: " + a + " ");
        System.out.print("B: " + b + " ");
        System.out.print("C: " + c + " ");
        System.out.println("X: " + x);
    }

    // static block (runs once when class loads)
    static {
        System.out.println("Static is Initialized.");
        b = a * 4;
    }
}

public class Ex22_static {

    public static void main(String[] args) {
        StaticDemo sd = new StaticDemo();
        StaticDemo.c = 5;
        for (int i = 0; i < 2; ++i) {
            sd.show(40 + i);
        }
        StaticDemo.show(10);
        System.out.println("B:" + StaticDemo.b);
        StaticDemo sd2 = new StaticDemo();
        //cout << sd2.a;
    }
}

/*
Key Notes:
1. static variable → one copy shared by all objects.
2. static method → can access only static members.
3. static block → runs once when the class is first loaded.
4. static members can be accessed using ClassName.member.
5. Static block is used for initialization of static variables.
*/
