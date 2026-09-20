
import java.io.FileOutputStream;
import java.io.OutputStream;

public class Ex4_FileOutputStreamDemo {

    public static void main(String args[]) throws Exception {

        String source = "Now is the time for all good men\n" + "to come to the aid of their country\n" + "and pay their due taxes.";

        byte buf[] = source.getBytes();

        OutputStream f0 = new FileOutputStream("D:/Documents/Code/CSE/OOP/2. KMS/Java codes/Part 2/5.File/file1.txt");

        for (int i = 0; i < buf.length; i += 2) {
            f0.write(buf[i]);
        }

        f0.close();

        OutputStream f1 = new FileOutputStream("D:/Documents/Code/CSE/OOP/KMS/Java codes/Part 2/5.File/file2.txt");

        f1.write(buf);

        f1.close();

        OutputStream f2 = new FileOutputStream("D:/Documents/Code/CSE/OOP/KMS/Java codes/Part 2/5.File/file3.txt");
        //System.out.println(buf.length);
        f2.write(buf, buf.length - buf.length / 4, buf.length / 4); // staring ending

        f2.close();
    }
}

/*
Key Notes:

1. FileOutputStream → writes bytes to file.
2. write():
   - write(int) → one byte
   - write(byte[]) → full array
   - write(byte[], offset, length)
3. getBytes() → converts String → byte array.
4. close() is mandatory (flushes data).
5. Used for writing binary/text files.
 */
