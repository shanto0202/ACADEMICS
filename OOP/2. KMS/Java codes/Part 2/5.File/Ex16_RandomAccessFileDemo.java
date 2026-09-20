
import java.io.RandomAccessFile;

public class Ex16_RandomAccessFileDemo {

    public static void main(String[] args) throws Exception {

        RandomAccessFile file = new RandomAccessFile("D:/Documents/Code/CSE/OOP/2. KMS/Java codes/Part 2/5.File/file1.txt", "rw");

        file.write("Hello".getBytes());
        System.out.println(file.getFilePointer());
        file.seek(0);
        System.out.println(file.getFilePointer());
        System.out.println(file.readLine());
        file.seek(10); //Hello-----World
        file.write("World".getBytes());
        file.seek(0);
        System.out.println(file.readLine());
        file.close();
    }
}

/*
Key Notes:

1. RandomAccessFile → read/write anywhere.
2. seek(position) → move pointer.
3. getFilePointer() → current position.
4. Works like array of bytes.
5. VERY IMPORTANT concept.
 */
