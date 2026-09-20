//package advanced;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class SharedClass4 {

    Lock lock = new ReentrantLock();

    void doSomething() {
        lock.lock();
        System.out.println(Thread.currentThread().getName() + " starts");
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            System.out.println("Interrupted");
        }
        System.out.println(Thread.currentThread().getName() + " finishes");
        lock.unlock();
    }
}

class ThreadSyncLock implements Runnable {

    SharedClass4 sharedClass;
    Thread t;

    public ThreadSyncLock(SharedClass4 s, String name) {
        sharedClass = s;
        t = new Thread(this, name);
        t.start();
    }

    public void run() {
        sharedClass.doSomething();
    }
}

public class Ex11_SynchronizationLock {

    public static void main(String[] args) {
        SharedClass4 sharedObject = new SharedClass4();
        ThreadSyncLock ob1 = new ThreadSyncLock(sharedObject, "T1");
        ThreadSyncLock ob2 = new ThreadSyncLock(sharedObject, "T2");
        ThreadSyncLock ob3 = new ThreadSyncLock(sharedObject, "T3");
        System.out.println(ob1);
        System.out.println(ob2);
        System.out.println(ob3);
    }
}

/*
Key Notes:

1. This program demonstrates Lock (alternative to synchronized).

2. According to slide:
   java.util.concurrent.locks provides Lock interface
   as an alternative to synchronized.

3. ReentrantLock:
   - implementation of Lock interface
   - allows a thread to acquire the same lock multiple times

4. lock.lock():
   - acquires the lock
   - if unavailable → thread waits

5. lock.unlock():
   - releases the lock
   - VERY IMPORTANT → must always be called

6. doSomething():
   - only one thread can execute at a time
   - ensures mutual exclusion (like synchronized)

7. Threads T1, T2, T3:
   - all try to access same shared object
   - but execution happens one by one due to lock

8. Advantage over synchronized:
   - more control
   - supports tryLock()
   - supports fairness policies
   - can be explicitly released

9. Important concept:
   Lock gives greater control over synchronization
   compared to synchronized keyword.

10. Best practice (not shown here but important):
    use try-finally:
    lock.lock();
    try { ... }
    finally { lock.unlock(); }

11. Slide connection:
    Lock interface → alternative synchronization mechanism
    ReentrantLock → commonly used implementation
*/