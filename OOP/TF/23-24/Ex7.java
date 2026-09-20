
abstract class X {

    X() {
        System.out.println("X Constructor");
        draw();
    }
    abstract void draw();
    abstract void process(int x);
    void process(Object o) {
        System.out.println("X process Object");
    }
}

class Y extends X {

    int y = 5;

    Y() {
        System.out.println("Y Constructor");
        //draw();
    }

    @Override
    void draw() {
        System.out.println("Y with y = " + y);
    }

    @Override
    void process(int x) {
        System.out.println("Y process int");
    }

    void process(String s) {
        System.out.println("Y process String");
    }
}

public class Ex7 {

    public static void main(String[] args) {

        X obj = new Y();

        obj.process(10);
        obj.process("hello");
        obj.process((Object) "hello");
    }
}

/*
Key Notes:

1. X is abstract:
   - cannot create object of X directly
   - can create reference of X

2. Object creation:
   - X obj = new Y();
   - first X constructor runs
   - then Y constructor runs

3. Constructor trap:
   - X constructor calls draw()
   - draw() is overridden in Y
   - so Y.draw() runs

4. Important:
   - during X constructor execution,
     Y's field y is not initialized to 5 yet
   - default value of int is 0
   - so output becomes: Y with y = 0

5. process(int):
   - declared in X, overridden in Y
   - runtime polymorphism
   - so obj.process(10) calls Y process int

6. process("hello"):
   - compiler checks reference type X
   - X has process(Object), not process(String)
   - String is converted to Object
   - so calls X process Object

7. process((Object) "hello"):
   - explicitly Object
   - so directly calls X process Object

8. Final output:
   X Constructor
   Y with y = 0
   Y Constructor
   Y process int
   X process Object
   X process Object
*/
