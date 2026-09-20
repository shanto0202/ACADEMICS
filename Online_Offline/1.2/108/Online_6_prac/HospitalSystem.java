
import java.util.*;

class Hospital {

    int[] beds;

    Hospital(int m) {
        beds = new int[m];
    }

    public synchronized void update(String name, char type, int ward) {
        beds[ward] += (type == 'a') ? 1 : -1;
        String action = (type == 'a') ? "admitted to" : "discharged from";
        System.out.println(name + " " + action + " ward " + ward);
    }
}

public class HospitalSystem {

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();
        int M = sc.nextInt();

        Hospital hospital = new Hospital(M);
        Thread[] threads = new Thread[N];

        for (int i = 0; i < N; i++) {
            int k = sc.nextInt();

            char[] types = new char[k];
            int[] wards = new int[k];

            for (int j = 0; j < k; j++) {
                types[j] = sc.next().charAt(0);
                wards[j] = sc.nextInt();
            }

            String name = "Staff-" + (i + 1);

            threads[i] = new Thread(() -> {
                for (int j = 0; j < k; j++) {
                    hospital.update(name, types[j], wards[j]);
                }
            });

            threads[i].start();
        }

        for (Thread t : threads) {
            t.join();
        }

        System.out.println("Final bed status:");
        for (int b : hospital.beds) {
            System.out.print(b + " ");
        }
    }
}
