//package threads;

class NewThread implements Runnable {

    String name; // name of thread
    Thread t;

    NewThread(String threadName) {
        name = threadName;
        t = new Thread(this, name);
        t.start(); // Start the thread
    }

    public void run() {
        System.out.println(name + " starting.");
        try {
            for (int i = 10; i > 0; i--) {
                System.out.println(name + ": " + i);
                Thread.sleep(100);
            }
        } catch (InterruptedException e) {
            System.out.println(name + "Interrupted");
        }
        System.out.println(name + " exiting.");
    }
}

public class Ex6_MultipleThreads {

    public static void main(String[] args) {
        System.out.println("Main thread starting.");
        NewThread t1 = new NewThread("One");

        // try {
        //     t1.t.join();
        // } catch (InterruptedException e) {
        //     System.out.println("Main thread Interrupted");
        // }
        
        NewThread t2 = new NewThread("Two");
        NewThread t3 = new NewThread("Three");
        // try {
        //     // wait for other threads to end
        //     Thread.sleep(500);
        // } catch (InterruptedException e) {
        //     System.out.println("Main thread Interrupted");
        // }
        System.out.println("Main thread exiting.");
    }
}
