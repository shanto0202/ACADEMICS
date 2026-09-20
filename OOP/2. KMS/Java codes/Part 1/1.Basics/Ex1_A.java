// Class Reference Example
public class Ex1_A {

    private int a;

    public Ex1_A() {
        this.a = 0; // constructor
    }
    

    public void setA(int a) {
        this.a = a;
    }

    public int getA() {
        return this.a;
    }

    public static void main(String args[]) {

        Ex1_A ob; // reference variable

        ob = new Ex1_A(); // object creation

        ob.setA(10);

        System.out.println(ob.getA());

    }
}

/*
Key Notes
---------
Reference variable:
Ex1_A ob;

Object creation:
new Ex1_A()

Members accessed using dot operator.
 */