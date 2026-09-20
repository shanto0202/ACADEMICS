
import java.util.*;

class Game {

    int[] score;

    Game(int m) {
        score = new int[m];
    }

    public synchronized void update(String name, char type, int player) {
        score[player] += (type == 'g') ? 1 : -1;
        String action = (type == 'g') ? "gained" : "lost";
        System.out.println(name + " " + action + " score for player " + player);
    }
}

public class GameSystem {

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();
        int M = sc.nextInt();

        Game game = new Game(M);
        Thread[] threads = new Thread[N];

        for (int i = 0; i < N; i++) {
            int k = sc.nextInt();

            char[] types = new char[k];
            int[] players = new int[k];

            for (int j = 0; j < k; j++) {
                types[j] = sc.next().charAt(0);
                players[j] = sc.nextInt();
            }

            String name = "User-" + (i + 1);

            threads[i] = new Thread(() -> {
                for (int j = 0; j < k; j++) {
                    game.update(name, types[j], players[j]);
                }
            });

            threads[i].start();
        }

        for (Thread t : threads) {
            t.join();
        }

        System.out.println("Final scores:");
        for (int s : game.score) {
            System.out.print(s + " ");
        }
    }
}
