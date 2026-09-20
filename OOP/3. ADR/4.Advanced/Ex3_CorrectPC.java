//package advanced;

class BufferC {

    int value;
    boolean valueSet = false;

    synchronized int consume() {
        // System.out.println(Thread.currentThread().getName() + " enters");
        while (!valueSet) { // always use while instead of if
            try {
                // System.out.println(Thread.currentThread().getName() + " waits");
                wait();
            } catch (InterruptedException e) {
                System.out.println("InterruptedException caught");
            }
        }
        System.out.println(Thread.currentThread().getName() + " consumes: " + value);
        valueSet = false;
        notifyAll(); // always use notifyAll instead of notify
        // System.out.println(Thread.currentThread().getName() + " exists");
        return value;
    }

    synchronized void produce(int value) {
        // System.out.println(Thread.currentThread().getName() + " enters");
        while (valueSet) { // always use while instead of if
            try {
                // System.out.println(Thread.currentThread().getName() + " waits");
                wait();
            } catch (InterruptedException e) {
                System.out.println("InterruptedException caught");
            }
        }
        this.value = value;
        valueSet = true;
        System.out.println(Thread.currentThread().getName() + " produces: " + this.value);
        notifyAll(); // always use notifyAll instead of notify
        // System.out.println(Thread.currentThread().getName() + " exists");
    }
}

class ProducerC implements Runnable {

    BufferC buffer;

    ProducerC(BufferC buffer, String name) {
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

class ConsumerC implements Runnable {

    BufferC buffer;

    ConsumerC(BufferC buffer, String name) {
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

public class Ex3_CorrectPC {

    public static void main(String[] args) {
        BufferC buffer = new BufferC();
        new ProducerC(buffer, "Producer");
        new ConsumerC(buffer, "Consumer");
        // new ConsumerC(buffer, "Consumer-2");
        System.out.println("Press Control-advanced.C to stop.");
    }
}

/*
Key Notes:

1. This is the CORRECT Producer-Consumer solution using:
   - synchronized
   - wait()
   - notifyAll()

2. wait():
   - releases the monitor(lock)
   - makes the current thread sleep
   - waits until another thread calls notify() / notifyAll()

3. notifyAll():
   - wakes up all waiting threads on the same object
   - one thread gets the monitor first
   - slide recommends best practice: use notifyAll()

4. valueSet is the condition variable:
   - true  → buffer contains data
   - false → buffer is empty

5. In consume():
   - if buffer is empty, consumer waits
   - when data is available, it consumes
   - then sets valueSet = false
   - then calls notifyAll()

6. In produce():
   - if buffer already has data, producer waits
   - when empty, producer writes value
   - sets valueSet = true
   - then calls notifyAll()

7. VERY IMPORTANT:
   wait() is used inside while loop, not if.

   Why?
   Because slides mention rare case of spurious wakeup:
   - a thread may wake up without notify()/notifyAll()
   - so condition must be checked again

8. Best practice from slide:
   - use wait() inside loop
   - use notifyAll() instead of notify()

9. Important rule from slide:
   wait(), notify(), notifyAll() can be called only inside synchronized method/block.

10. This solves the communication problem that existed in:
    - PollingPC
    - IncorrectPC

11. Exam learning flow:
    PollingPC → IncorrectPC → CorrectPC

12. This is the elegant inter-thread communication mechanism described in the slide.
*/