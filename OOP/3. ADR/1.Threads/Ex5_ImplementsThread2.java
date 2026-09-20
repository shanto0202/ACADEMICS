//package threads;

class NewThread3 implements Runnable {

    @Override
    public void run() {
        try {
            for (int i = 10; i > 0; i--) {
                System.out.println("Child Thread: " + i);
                Thread.sleep(250);
            }
        } catch (InterruptedException e) {
            System.out.println("Child interrupted.");
        }
        System.out.println("Exiting child thread.");
    }
}

public class Ex5_ImplementsThread2 {

    public static void main(String[] args) {
        Runnable r = new NewThread3();
        //Thread t2 = new Thread(new NewThread3());
        //t2.start();
        Thread t = new Thread(r);
        t.start();
    }
}
