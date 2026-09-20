
import java.io.*;

public class Ex14_DataIODemo {

    public static void main(String args[]) throws Exception {

        FileOutputStream fos = new FileOutputStream("output.txt");
        DataOutputStream dos = new DataOutputStream(fos);

        dos.writeDouble(98.6);
        dos.writeInt(1000);
        dos.writeBoolean(true);

        dos.close();
        fos.close();

        FileInputStream fis = new FileInputStream("output.txt");
        DataInputStream dis = new DataInputStream(fis);

        double d = dis.readDouble();
        int i = dis.readInt();
        boolean b = dis.readBoolean();

        System.out.println(d);
        System.out.println(i);
        System.out.println(b);

        dis.close();
        fis.close();
    }
}

/*
Key Notes:

1. Reads/writes primitive types.
2. Maintains exact data format.
3. Must read in same order as written.
4. Useful for structured binary data.
*/