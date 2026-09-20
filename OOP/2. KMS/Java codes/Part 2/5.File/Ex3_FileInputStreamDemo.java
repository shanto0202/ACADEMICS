
import java.io.FileInputStream;
import java.io.InputStream;

public class Ex3_FileInputStreamDemo {

    public static void main(String args[]) throws Exception {

        int size;

        InputStream f = new FileInputStream("sample.txt");

        System.out.println("Total Available Bytes: " + (size = f.available()));

        int n = size / 4; // 13 / 4 = 3

        System.out.println("Reading first " + n + " bytes:");

        for (int i = 0; i < n; i++) {
            System.out.print((char) f.read());
        }

        System.out.println("\nRemaining: " + f.available());

        System.out.println("Reading next " + n + " bytes:");

        byte b[] = new byte[n];

        if (f.read(b) != n) {
            System.out.println("Couldn't read properly"); //
        }

        System.out.println(new String(b, 0, n));

        System.out.println("Remaining: " + (size = f.available()));

        System.out.println("Skipping half:");

        f.skip(size / 2);

        System.out.println("Remaining: " + f.available());

        System.out.println("Reading more:");

        if (f.read(b, n / 2, n / 2) != n / 2) {
            System.out.println("Couldn't read properly");
        }

        System.out.println(new String(b, 0, b.length));

        System.out.println("Remaining: " + f.available());
    }
}

/*
Key Notes:

1. FileInputStream → reads bytes from file.
2. available() → number of bytes remaining.
3. read():
   - read() → one byte
   - read(byte[]) → multiple bytes
4. skip(n) → skip bytes.
5. Returns -1 at EOF (important concept).
6. Used for binary data (images, files).
*/
