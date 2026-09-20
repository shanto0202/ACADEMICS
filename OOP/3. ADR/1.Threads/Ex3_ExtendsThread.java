//package threads;

class NewThread2 extends Thread {
    NewThread2() {
        super("Extends Thread");
        //start();
    }
    // This is the entry point for the thread.
    @Override
    public void run() {
        System.out.println(Thread.currentThread().getName());
        System.out.println("Starting child thread.");
        try {
            for (int i = 5; i > 0; i--) {
                System.out.println("Child Thread: " + i);
                Thread.sleep(250);
            }
        } catch (InterruptedException e) {
            System.out.println("Child interrupted.");
        }
        System.out.println("Exiting child thread.");
    }
}

public class Ex3_ExtendsThread {

    public static void main(String[] args) throws Exception {
        NewThread2 newThread2 = new NewThread2();
        newThread2.start();
        //newThread2.run();
        for (int i = 10; i > 0; i--) {
            System.out.println("Main Thread: " + i);
            Thread.sleep(500);
        }
    }
}
