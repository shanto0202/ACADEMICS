// TF
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

public class Ex5_FileCopyDemo {

    public static void main(String args[]) throws Exception {

        String source = "D:/Documents/Code/CSE/OOP/KMS/Java codes/Part 2/5.File/sample.txt";
        String destination = "D:/Documents/Code/CSE/OOP/KMS/Java codes/Part 2/5.File/output.txt";

        InputStream in = new FileInputStream(source);
        OutputStream out = new FileOutputStream(destination);

        byte[] b = new byte[4];

        System.out.println(in.available() + " " + b.length);
        int chunks = in.available() / b.length;

        for (int i = 0; i < chunks; i++) {
            in.read(b);
            out.write(b);
            //out.write();
        }

        b = new byte[in.available()];
        //System.out.println(in.available());

        in.read(b);
        out.write(b);

        in.close();
        out.close();
    }
}

/*
Key Notes:

1. Used to copy files (binary safe).
2. Uses buffer (byte array) → efficient.
3. Reads chunk by chunk → faster.
4. InputStream → read source.
5. OutputStream → write destination.
6. VERY IMPORTANT real-world example.
 */
