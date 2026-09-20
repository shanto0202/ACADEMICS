
class Base {

    public int x;
    private int y;
    protected int z;
    int b; //default

    public void setY(int n) {
        y = n;
    }

    public int getY() {
        return y;
    }

    protected int getSum() { // can be accessed from subclass
        return x + y;
    } // base method
}

class Derived extends Base { // inheritance

    public void setZ(int n) {
        z = n;
        //x = n; //okay
        //b = n; //okay
    }

    public int getZ() {
        return z;
    }

    public void showSum() {
        System.out.println(getSum() + z); // use inherited method
    }
}

public class Ex1_Java_access_specifier {

    public static void main(String[] args) {
        Derived myObj = new Derived();
        myObj.x = 5;
        myObj.setY(4); // private via method
        myObj.setZ(7);
        myObj.showSum();
    }
}

/*
Key Notes:

1. Demonstrates public, private, and protected members.

2. private member y is accessed through setter/getter.

3. protected member z and protected method getSum() are usable in Derived.

4. Output: 16
 */
