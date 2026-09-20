
import java.util.*;

class VotingSystem {

    int[] votes;

    VotingSystem(int m) {
        votes = new int[m];
    }

    public synchronized void update(String name, char type, int candidate) {
        if (type == 'v') {
            votes[candidate]++;
            System.out.println(name + " voted candidate " + candidate);
        } else {
            if (votes[candidate] > 0) {
                votes[candidate]--;
                System.out.println(name + " unvoted candidate " + candidate);
            } else {
                System.out.println(name + " tried to unvote candidate " + candidate + " but vote is already 0");
            }
        }
    }
}

public class Voting {

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt(); // users
        int M = sc.nextInt(); // candidates

        VotingSystem vs = new VotingSystem(M);
        Thread[] threads = new Thread[N];

        for (int i = 0; i < N; i++) {
            int k = sc.nextInt();

            char[] types = new char[k];
            int[] cand = new int[k];

            for (int j = 0; j < k; j++) {
                types[j] = sc.next().charAt(0);
                cand[j] = sc.nextInt();
            }

            String name = "User-" + (i + 1);

            threads[i] = new Thread(() -> {
                for (int j = 0; j < k; j++) {
                    vs.update(name, types[j], cand[j]);
                }
            });

            threads[i].start();
        }

        for (Thread t : threads) {
            t.join();
        }

        System.out.println("Final vote count:");
        for (int v : vs.votes) {
            System.out.print(v + " ");
        }
    }
}
