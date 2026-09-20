//TF
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.Reader;

public class Ex8_BufferedReaderDemo {

    public static void main(String args[]) throws Exception {

        Reader fr = new FileReader("D:/Documents/Code/CSE/OOP/2. KMS/Java codes/Part 2/5.File/sample.txt");
        BufferedReader br = new BufferedReader(fr);

        while (true) {
            String s = br.readLine();
            if (s == null) {
                break;
            }
            System.out.println(s);
            System.out.println("null");
        }

        br.close();
        fr.close();
    }
}

/*
Key Notes:

1. BufferedReader → improves performance.
2. readLine() → reads one line at a time.
3. Faster than FileReader alone.
4. Used in real-world applications.
 */
