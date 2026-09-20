import java.util.*;
class Inventory {
    int[] stock;
    Inventory(int m) {
        stock = new int[m];
    }
    public synchronized void update(String name, char type, int item) {
        stock[item] += (type == 'a') ? 1 : -1;
        String action = (type == 'a') ? "added" : "removed";
        System.out.println(name + " " + action + " item " + item);
    }
}

public class Party {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt(), M = sc.nextInt();
        Inventory inv = new Inventory(M);
        Thread[] threads = new Thread[N];
        for (int i = 0; i < N; i++) {
            int k = sc.nextInt();
            char[] types = new char[k];
            int[] items = new int[k];
            // Read all actions for this friend first
            for (int j = 0; j < k; j++) {
                types[j] = sc.next().charAt(0);
                items[j] = sc.nextInt();
            }
            String name = "Friend-" + (i + 1);
            // Lambda replaces the entire FriendTask class
            threads[i] = new Thread(() -> {
                for (int j = 0; j < k; j++) {
                    inv.update(name, types[j], items[j]);
                }
            });
            threads[i].start();
        }
        // Wait for all threads
        for (Thread t : threads) {
            t.join();
        }
        
        System.out.println("Final inventory status:");
        for (int s : inv.stock) {
            System.out.print(s + " ");
        }
    }
}
//salami_nai