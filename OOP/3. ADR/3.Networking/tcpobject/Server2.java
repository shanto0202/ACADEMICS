import java.io.*;
import java.net.*;
import java.util.*;

public class Server2 {

    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(4444);
            while (true) {
                Socket s = ss.accept();
                System.out.println("Client connected!");
                new Servant(s);
            }
        } catch (IOException e) {
            System.out.println("Server error: " + e.getMessage());
        }
    }
}

class Servant implements Runnable {

    private final Socket s;
    private final Thread t;

    public Servant(Socket s) {
        this.s = s;
        t = new Thread(this);
        t.start();
    }

    @Override
    public void run() {
        try (
                ObjectOutputStream oos = new ObjectOutputStream(s.getOutputStream()); ObjectInputStream ois = new ObjectInputStream(s.getInputStream())) {
            Integer a = (Integer) ois.readObject();
            System.out.println("Read a: " + a);
            Integer b = (Integer) ois.readObject();
            System.out.println("Input received form client!");
            oos.writeObject(noOfFibo(a, b));
            oos.flush();
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("Servant error: " + e.getMessage());
        }
    }

    private int noOfFibo(int a, int b) {
        ArrayList<Integer> starters = fiboFinder(a);
        int p1 = starters.get(0);
        int p2 = starters.get(1);
        if (b < p1) { //a<b<p1<p2
            return 0;
        } else if (b < p2) { // a<p1<b<p2
            return 1;
        }
        int c = 2;
        while (p2 <= b) {
            int nxt = p1 + p2;
            p1 = p2;
            p2 = nxt;
            c++;
        }
        return c;
    }

    private ArrayList<Integer> fiboFinder(int a) {
        ArrayList<Integer> fib = new ArrayList<>();
        int p1 = 0;
        int p2 = 1;
        int next;
        while (p1 < a) {
            next = p1 + p2;
            p1 = p2;
            p2 = next;
        }
        fib.add(p1);
        fib.add(p2);
        return fib;
    }
}
