
import java.io.FileWriter;
import java.io.Writer;
import java.nio.charset.StandardCharsets;

public class Ex7_FileWriterDemo {

    public static void main(String args[]) throws Exception {

        String source = "Now is the time for all good men\n" + "to come to the aid of their country\n" + "and pay their due taxes.";

        char buffer[] = new char[source.length()];

        source.getChars(0, source.length(), buffer, 0);

        Writer f0 = new FileWriter("D:/Documents/Code/CSE/OOP/2. KMS/Java codes/Part 2/5.File/file1.txt");

        for (int i = 0; i < buffer.length; i += 2) {
            f0.write(buffer[i]);
        }

        f0.close();

        FileWriter f1 = new FileWriter("D:/Documents/Code/CSE/OOP/2. KMS/Java codes/Part 2/5.File/file2.txt");
        f1.write(buffer);
        f1.close();

        FileWriter f2 = new FileWriter("D:/Documents/Code/CSE/OOP/2. KMS/Java codes/Part 2/5.File/file3.txt");
        f2.write(buffer, buffer.length - buffer.length / 4, buffer.length / 4);
        f2.close();

        FileWriter fw = new FileWriter("out.txt", StandardCharsets.UTF_8);
        fw.write("ক"); // Unicode write
        fw.close();
    }
}

/*
Key Notes:

1. FileWriter → character output stream.
2. write():
   - single char
   - char[]
   - partial write
3. Supports Unicode (UTF-8).
4. Used for text writing.
5. getChars() → convert String → char array.
*/
