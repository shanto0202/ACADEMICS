
import java.util.*;

class StudentManager {

    int[] courses;

    StudentManager(int m) {
        courses = new int[m];
    }

    public synchronized void update(String name, char type, int course) {
        courses[course] += (type == 'j') ? 1 : -1;
        String action = (type == 'j') ? "joined" : "left";
        System.out.println(name + " " + action + " course " + course);
    }
}

public class Student {

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt(); // students
        int M = sc.nextInt(); // courses
        StudentManager sm = new StudentManager(M);
        Thread[] threads = new Thread[N];

        for (int i = 0; i < N; i++) {
            int k = sc.nextInt();

            char[] types = new char[k];
            int[] courses = new int[k];

            for (int j = 0; j < k; j++) {
                types[j] = sc.next().charAt(0);
                courses[j] = sc.nextInt();
            }

            String name = "Student-" + (i + 1);

            threads[i] = new Thread(() -> {
                for (int j = 0; j < k; j++) {
                    sm.update(name, types[j], courses[j]);
                }
            });

            threads[i].start();
        }

        for (Thread t : threads) {
            t.join();
        }

        System.out.println("Final course enrollments:");
        for (int c : sm.courses) {
            System.out.print(c + " ");
        }
    }
}
