
import java.io.*;
import java.nio.charset.StandardCharsets;

public class Ex11_UnicodeReadWrite {

    public static void main(String args[]) throws Exception {

        Reader reader = new InputStreamReader( new FileInputStream("D:/Documents/Code/CSE/OOP/2. KMS/Java codes/Part 2/5.File/file1.txt"),StandardCharsets.UTF_8);

        BufferedReader br = new BufferedReader(reader);

        Writer writer = new OutputStreamWriter(new FileOutputStream("D:/Documents/Code/CSE/OOP/2. KMS/Java codes/Part 2/5.File/file2.txt"),StandardCharsets.UTF_8);

        BufferedWriter bw = new BufferedWriter(writer);

        String s;

        while (true) {
            s = br.readLine();
            if (s == null) {
                break;
            }

            System.out.println(s);

            bw.write(s);
            bw.newLine();
        }

        br.close();
        bw.close();
    }
}

/*
Key Notes:

1. Handles Unicode properly (UTF-8).
2. InputStreamReader → byte → char conversion.
3. OutputStreamWriter → char → byte conversion.
4. Required for international text (Bangla, etc).
*/
