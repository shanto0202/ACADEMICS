//package advanced;

class Buffer {

    int value;

    synchronized int consume() {
        System.out.println(Thread.currentThread().getName() + " consumes: " + value);
        return value;
    }

    synchronized void produce(int value) {
        this.value = value;
        System.out.println(Thread.currentThread().getName() + " produces: " + this.value);
    }
}

class Producer implements Runnable {

    Buffer buffer;

    Producer(Buffer buffer, String name) {
        this.buffer = buffer;
        new Thread(this, name).start();
    }

    public void run() {
        int i = 0;
        while (i < 100) {
            buffer.produce(i++);
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}

class Consumer implements Runnable {

    Buffer buffer;

    Consumer(Buffer buffer, String name) {
        this.buffer = buffer;
        new Thread(this, name).start();
    }

    public void run() {
        int i = 0;
        while (i++ < 100) {
            buffer.consume();
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}

public class Ex2_IncorrectPC {

    public static void main(String[] args) {
        Buffer buffer = new Buffer();
        new Producer(buffer, "Producer");
        new Consumer(buffer, "Consumer");
        System.out.println("Press Control-advanced.C to stop.");
    }
}

/*
Key Notes:

1. This is an INCORRECT implementation of Producer-Consumer.

2. synchronized is used:
   - ensures mutual exclusion (only one thread at a time)
   - prevents data corruption

3. BUT problem:
   - No coordination between producer and consumer
   - Consumer may read old value multiple times
   - Producer may overwrite value before consumer reads

4. Missing concept:
   - No condition checking (like valueSet)
   - No waiting mechanism (wait(), notify())

5. So even though synchronized is used:
   ❌ It does NOT solve inter-thread communication

6. This shows:
   synchronization ≠ communication

7. According to slides:
   Proper communication requires:
   - wait()
   - notify()
   - notifyAll()
   (must be used inside synchronized block)

8. Major issue:
   - Consumer does not know when new data is available
   - Producer does not know when buffer is consumed

9. This example is intentionally WRONG to show:
   why polling and naive synchronization are insufficient

10. Learning flow (very important for exam):
    Polling → IncorrectPC → CorrectPC

11. Slide reference:
    Inter Thread Communication → proper mechanism uses wait/notify
*/