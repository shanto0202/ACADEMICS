
import java.util.*;

class Bank {

    int[] balance;

    Bank(int m) {
        balance = new int[m];
    }

    public synchronized void update(String name, char type, int acc) {
        balance[acc] += (type == 'd') ? 1 : -1;
        String action = (type == 'd') ? "deposited to" : "withdrew from";
        System.out.println(name + " " + action + " account " + acc);
    }
}

public class bank {

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt(); // number of people
        int M = sc.nextInt(); // number of accounts

        Bank bank = new Bank(M);
        Thread[] threads = new Thread[N];

        for (int i = 0; i < N; i++) {
            int k = sc.nextInt();

            char[] types = new char[k];
            int[] accs = new int[k];

            for (int j = 0; j < k; j++) {
                types[j] = sc.next().charAt(0); // d or w
                accs[j] = sc.nextInt();
            }

            String name = "User-" + (i + 1);

            threads[i] = new Thread(() -> {
                for (int j = 0; j < k; j++) {
                    bank.update(name, types[j], accs[j]);
                }
            });

            threads[i].start();
        }

        for (Thread t : threads) {
            t.join();
        }

        System.out.println("Final balances:");
        for (int b : bank.balance) {
            System.out.print(b + " ");
        }
    }
}
