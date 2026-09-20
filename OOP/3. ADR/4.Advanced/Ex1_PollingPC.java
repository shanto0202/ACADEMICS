//package advanced;

class PollingBuffer {

    int value;
    volatile boolean valueSet = false;

    void consume() {
        while (!valueSet) {

        }
        valueSet = false;
        System.out.println(Thread.currentThread().getName() + " consumes: " + value);
    }

    void produce(int value) {
        while (valueSet) {

        }
        this.value = value;
        this.valueSet = true;
        System.out.println(Thread.currentThread().getName() + " produces: " + this.value);
    }
}

class PollingProducer implements Runnable {

    PollingBuffer buffer;

    PollingProducer(PollingBuffer buffer, String name) {
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

class PollingConsumer implements Runnable {

    PollingBuffer buffer;

    PollingConsumer(PollingBuffer buffer, String name) {
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

public class Ex1_PollingPC {

    public static void main(String[] args) {
        PollingBuffer buffer = new PollingBuffer();
        new PollingProducer(buffer, "Producer");
        new PollingConsumer(buffer, "Consumer");
        System.out.println("Press Control-advanced.C to stop.");
    }
}

/*
Key Notes:

1. This code demonstrates polling in Producer-Consumer.
2. Polling means repeatedly checking a condition in a loop.
   - Consumer waits using: while (!valueSet) { }
   - Producer waits using: while (valueSet) { }

3. Problem of polling:
   - wastes CPU time
   - thread keeps running in busy waiting
   - inefficient approach

4. volatile boolean valueSet is used so that changes made by one thread
   become visible to the other thread immediately.

5. produce():
   - waits until buffer is empty
   - puts a value
   - marks valueSet = true

6. consume():
   - waits until buffer has data
   - reads value
   - marks valueSet = false

7. This is NOT the elegant Java solution.
   According to the slide, better inter-thread communication is done by:
   - wait()
   - notify()
   - notifyAll()

8. This example is important because it shows the "old / inefficient" idea first,
   before learning the correct synchronized wait-notify version.

9. Exam point:
   Polling = repeated checking of condition, wastes CPU.

10. This code is related to the slide topic:
    Inter Thread Communication → "One way is to use polling"
 */