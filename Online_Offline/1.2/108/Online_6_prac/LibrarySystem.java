
import java.util.*;

class Library {

    int[] books;

    Library(int m) {
        books = new int[m];
    }

    public synchronized void update(String name, char type, int book) {
        books[book] += (type == 'r') ? 1 : -1;
        String action = (type == 'r') ? "returned" : "borrowed";
        System.out.println(name + " " + action + " book " + book);
    }
}

public class LibrarySystem {

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt(); // users
        int M = sc.nextInt(); // books

        Library lib = new Library(M);
        Thread[] threads = new Thread[N];

        for (int i = 0; i < N; i++) {
            int k = sc.nextInt();

            char[] types = new char[k];
            int[] books = new int[k];

            for (int j = 0; j < k; j++) {
                types[j] = sc.next().charAt(0);
                books[j] = sc.nextInt();
            }

            String name = "User-" + (i + 1);

            threads[i] = new Thread(() -> {
                for (int j = 0; j < k; j++) {
                    lib.update(name, types[j], books[j]);
                }
            });

            threads[i].start();
        }

        for (Thread t : threads) {
            t.join();
        }

        System.out.println("Final library stock:");
        for (int b : lib.books) {
            System.out.print(b + " ");
        }
    }
}
