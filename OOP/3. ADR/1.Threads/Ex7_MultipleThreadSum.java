//package threads;

class SumThread implements Runnable {

    public Thread t;
    public int sum = 0;
    private int start = 0;
    private int end = 0;

    SumThread(int start, int end) {
        this.start = start;
        this.end = end;
        this.t = new Thread(this);
        this.t.start();
    }

    public void run() {
        for (int i = start; i <= end; i++) {
            sum += i;
        }
    }
}

public class Ex7_MultipleThreadSum {

    public static void main(String[] args) {
        SumThread t1 = new SumThread(1, 5);
        SumThread t2 = new SumThread(6, 10);
        SumThread t3 = new SumThread(11, 15);
        SumThread t4 = new SumThread(16, 20);

        try {
            // wait for other threads to end
            t1.t.join();
            t2.t.join();
            t3.t.join();
            t4.t.join();
        } catch (InterruptedException e) {
            System.out.println("Main thread Interrupted");
        }

        System.out.println(t1.sum + t2.sum + t3.sum + t4.sum);
    }
}
