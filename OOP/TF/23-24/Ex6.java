
class X {

    static int a = 1;

    void display() {
        Y obY = new Y();
        obY.display();
        Z obZ = new Z();
        obZ.display();
    }

    void showNested() {
        Y obY = new Y();
        Z obZ = new Z();
        System.out.println(obY.b);
        System.out.println(obZ.c);
    }

    class Y {

        int b = 2;

        void display() {
            System.out.println(a);
            System.out.println(b);
        }
    }

    static class Z {

        int c = 3;

        void display() {
            System.out.println(a); //it can not directly access non static variable
            System.out.println(c);
        }
    }
}

public class Ex6 {

    public static void main(String[] args) {

        X obX = new X();

        obX.display();
        obX.showNested();

        X.Y obY = obX.new Y(); // non static inner class tied with outer class obj
        obY.display();

        X.Z obZ = new X.Z(); //static are not
        obZ.display();
    }
}

/*
Key Notes:

1. X has:
   - instance variable a = 1
   - inner class Y
   - static nested class Z

2. Y is non-static inner class:
   - it can directly access outer class instance variable a
   - because it is tied to an object of X

3. Z is static nested class:
   - it CANNOT directly access non-static variable a
   - so we pass X object as parameter:
     display(X obX)

4. showNested():
   - cannot directly write b or c
   - must create objects of Y and Z first

5. Object creation rules:
   - Y obY = new Y();          // valid inside X
   - X.Y obY = obX.new Y();    // valid outside X
   - X.Z obZ = new X.Z();      // valid for static nested class

6. Main method:
   - creates object of X
   - calls all methods correctly
   - creates Y and Z properly

7. Important exam idea:
   - non-static inner class needs outer object
   - static nested class does not need outer object
 */
