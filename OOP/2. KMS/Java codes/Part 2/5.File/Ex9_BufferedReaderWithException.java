
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Ex9_BufferedReaderWithException {

    public static void main(String args[]) {

        try (BufferedReader br = new BufferedReader(new FileReader("D:/Documents/Code/CSE/OOP/2. KMS/Java codes/Part 2/5.File/sample.txt"))) {

            while (true) {
                String s = br.readLine();
                if (s == null) {
                    break;
                }
                System.out.println(s);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

/*
Key Notes:

1. try-with-resources → auto close stream.
2. No need for finally block.
3. Cleaner and safer code.
4. VERY IMPORTANT modern Java practice.
*/
