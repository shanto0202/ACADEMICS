
import java.io.File;
import java.util.Date;

public class Ex1_FileDemo {

    static void p(String s) {
        System.out.println(s);
    }

    public static void main(String args[]) {

        File f1 = new File("D:/Documents/Code/CSE/OOP/KMS/Java codes/Part 2/5.File/sample.txt");

        p("File Name: " + f1.getName());
        p("Path: " + f1.getPath());
        p("Absolute Path: " + f1.getAbsolutePath());
        p("Parent: " + f1.getParent());

        p(f1.exists() ? "exists" : "does not exist");

        p(f1.canWrite() ? "is writable" : "is not writable");
        p(f1.canRead() ? "is readable" : "is not readable");

        p("is " + (f1.isDirectory() ? "" : "not ") + "a directory");
        p(f1.isFile() ? "is normal file" : "not a normal file");

        p("Last Modified: " + f1.lastModified());

        Date date = new Date(f1.lastModified());
        p(date.toString());

        Date current = new Date();
        p("Current Date: " + current.toString());

        p("File size: " + f1.length() + " bytes");
    }
}

/*
Key Notes:

1. File class is used for metadata (NOT for reading/writing).
2. Important methods:
   - getName(), getPath(), getAbsolutePath()
   - exists(), canRead(), canWrite()
   - isFile(), isDirectory()
   - length() → size in bytes
3. lastModified() → returns time in milliseconds.
4. File object does NOT create file automatically.
5. VERY IMPORTANT: File class ≠ File I/O (just info).
 */