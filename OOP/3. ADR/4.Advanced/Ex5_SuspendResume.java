//package advanced;

// Suspending and resuming a thread the modern way.
class NewThreadSR implements Runnable {

    String name; // name of thread
    Thread t;
    boolean suspendFlag;

    NewThreadSR(String threadname) {
        name = threadname;
        t = new Thread(this, name);
        System.out.println("New thread: " + t);
        suspendFlag = false;
        t.start(); // Start the thread
    }

    // This is the entry point for thread.
    public void run() {
        try {
            for (int i = 15; i > 0; i--) {
                System.out.println(name + ": " + i);
                Thread.sleep(200);
                synchronized (this) {
                    while (suspendFlag) {
                        wait();
                    }
                }
            }
        } catch (InterruptedException e) {
            System.out.println(name + " interrupted.");
        }
        System.out.println(name + " exiting.");
    }

    synchronized void mySuspend() {
        suspendFlag = true;
    }

    synchronized void myResume() {
        suspendFlag = false;
        notify();
    }
}

public class Ex5_SuspendResume {

    public static void main(String[] args) {
        NewThreadSR ob1 = new NewThreadSR("One");
        NewThreadSR ob2 = new NewThreadSR("Two");
        try {
            Thread.sleep(1000);
            ob1.mySuspend();
            System.out.println("Suspending thread One");
            Thread.sleep(1000);
            ob1.myResume();
            System.out.println("Resuming thread One");
            ob2.mySuspend();
            System.out.println("Suspending thread Two");
            Thread.sleep(1000);
            ob2.myResume();
            System.out.println("Resuming thread Two");
        } catch (InterruptedException e) {
            System.out.println("advanced.Main thread Interrupted");
        }
        // wait for threads to finish
        try {
            System.out.println("Waiting for threads to finish.");
            ob1.t.join();
            ob2.t.join();
        } catch (InterruptedException e) {
            System.out.println("advanced.Main thread Interrupted");
        }
        System.out.println("advanced.Main thread exiting.");
    }
}

/*
Key Notes:

1. This code shows the modern way to suspend and resume a thread.

2. According to the slide:
   old methods were:
   - suspend()
   - resume()
   - stop()
   These methods are deprecated.

3. Why deprecated?
   - suspend() may keep locks unreleased
   - can cause deadlock
   - stop() may corrupt shared data
   - unsafe for system stability

4. So instead of using t.suspend() and t.resume(),
   this program uses:
   - a boolean flag (suspendFlag)
   - wait()
   - notify()

5. How it works:
   - mySuspend() sets suspendFlag = true
   - in run(), thread checks the flag
   - if true, thread waits
   - myResume() sets suspendFlag = false
   - then notify() wakes the waiting thread

6. VERY IMPORTANT:
   while (suspendFlag) { wait(); }
   is safer than if, because condition is rechecked after waking up.

7. synchronized is needed because:
   - wait() and notify() must be called inside synchronized context
   - shared variable suspendFlag is accessed safely

8. join() is used in main thread to wait for both threads to finish.

9. This code does not use deprecated thread control methods directly.
   Instead, it implements suspend/resume behavior safely.

10. Slide connection:
    "Suspend, Resume and Stop" topic explains why old thread control
    methods are dangerous, and this code demonstrates the safer approach.
*/
