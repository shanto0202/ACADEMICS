
import java.io.File;

public class Ex2_DirectoryDemo {

    public static void main(String args[]) {

        String dirname = "D:/Documents/Code/CSE/OOP/KMS/Java codes/Part 2";

        File f1 = new File(dirname);

        if (f1.isDirectory()) {

            System.out.println("Directory of " + dirname);

            String s[] = f1.list();

            for (int i = 0; i < s.length; i++) {

                File f = new File(dirname + "/" + s[i]); //Example 1

                if (f.isDirectory()) {
                    System.out.println(s[i] + " is a directory");
                } else {
                    System.out.println(s[i] + " is a file");
                }
            }

        } else {
            System.out.println(dirname + " is not a directory");
        }
    }
}

/*
Key Notes:

1. Directory is also treated as File in Java.
2. list() → returns names of files/folders.
3. listFiles() → returns File objects.
4. isDirectory() → check folder.
5. Used for file system traversal.
*/