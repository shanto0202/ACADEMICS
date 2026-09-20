
import java.io.*;

public class Ex13_ObjectDeSerializationDemo {

    public static void main(String args[]) {

        try {
            FileInputStream fis = new FileInputStream("serial");
            ObjectInputStream ois = new ObjectInputStream(fis);

            MyClass obj = (MyClass) ois.readObject();

            System.out.println(obj);

            ois.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}

/*
Key Notes:

1. Deserialization → file → object.
2. ObjectInputStream used.
3. Must cast object.
4. Restores object state.
*/
