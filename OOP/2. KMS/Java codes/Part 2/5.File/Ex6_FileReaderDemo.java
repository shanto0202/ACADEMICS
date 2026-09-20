
import java.io.File;
import java.io.FileReader;
import java.io.Reader;

public class Ex6_FileReaderDemo {

    public static void main(String args[]) throws Exception {

        File f = new File("D:/Documents/Code/CSE/OOP/2. KMS/Java codes/Part 2/5.File/file1.txt");

        Reader fr = new FileReader(f);

        char data[] = new char[(int) f.length()];

        fr.read(data);

        System.out.println(new String(data));

        fr.close();
    }
}

/*
Key Notes:

1. FileReader → character stream (text file).
2. Reads characters instead of bytes.
3. Better than FileInputStream for text.
4. read(char[]) → reads entire file.
5. Always close stream.
*/