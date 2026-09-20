
import java.io.*;

class MyClass implements Serializable {

    String s;
    int i;
    double d;

    public MyClass(String s, int i, double d) {
        this.s = s;
        this.i = i;
        this.d = d;
    }

    public String toString() { //
        return "s=" + s + "; i=" + i + "; d=" + d;
    }
}

public class Ex12_ObjectSerializationDemo {

    public static void main(String args[]) {

        try {
            MyClass obj1 = new MyClass("Hello", -7, 2.7e10);

            FileOutputStream fos = new FileOutputStream("serial");
            ObjectOutputStream oos = new ObjectOutputStream(fos); // object to byte stream

            oos.writeObject(obj1); //serialization happens here

            oos.close();
            System.out.println(obj1);

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}

/*
Key Notes:

1. Serialization → object → file.
2. Must implement Serializable interface.
3. ObjectOutputStream used.
4. Saves object state.
*/
