
import java.util.*;

class Market {

    int[] items;

    Market(int m) {
        items = new int[m];
    }

    public synchronized void update(String name, char type, int item) {
        items[item] += (type == 'a') ? 1 : -1;
        String action = (type == 'a') ? "scanned" : "removed";
        System.out.println(name + " " + action + " item " + item);
    }
}

public class Supermarket {

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();
        int M = sc.nextInt();

        Market market = new Market(M);
        Thread[] threads = new Thread[N];

        for (int i = 0; i < N; i++) {
            int k = sc.nextInt();

            char[] types = new char[k];
            int[] items = new int[k];

            for (int j = 0; j < k; j++) {
                types[j] = sc.next().charAt(0);
                items[j] = sc.nextInt();
            }

            String name = "Cashier-" + (i + 1);

            threads[i] = new Thread(() -> {
                for (int j = 0; j < k; j++) {
                    market.update(name, types[j], items[j]);
                }
            });

            threads[i].start();
        }

        for (Thread t : threads) {
            t.join();
        }

        System.out.println("Final billing status:");
        for (int x : market.items) {
            System.out.print(x + " ");
        }
    }
}
