//package advanced;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

class ProducerB implements Runnable {

    BlockingQueue<Integer> queue;

    ProducerB(BlockingQueue<Integer> queue, String name) {
        this.queue = queue;
        new Thread(this, name).start();
    }

    public void run() {
        int i = 0;
        try {
            while (true) {
                queue.put(i++);
                System.out.println(Thread.currentThread().getName() + " produces: " + (i - 1));
            }
        } catch (InterruptedException e) {
            System.out.println("Interrupted");
        }
    }
}

class ConsumerB implements Runnable {

    BlockingQueue<Integer> queue;

    ConsumerB(BlockingQueue<Integer> queue, String name) {
        this.queue = queue;
        new Thread(this, name).start();
    }

    public void run() {
        try {
            while (true) {
                System.out.println(Thread.currentThread().getName() + " consumes: " + queue.take());
            }
        } catch (InterruptedException e) {
            System.out.println("Interrupted");
        }
    }
}

public class Ex9_PCBlockingQueue {

    public static void main(String[] args) {
        BlockingQueue<Integer> queue = new ArrayBlockingQueue<>(1);
        new ProducerB(queue, "Producer");
        new ConsumerB(queue, "Consumer");
        System.out.println("Press Control-C to stop.");
    }
}

/*
Key Notes:

1. This is Producer-Consumer using BlockingQueue (modern approach).

2. BlockingQueue is part of:
   java.util.concurrent (Concurrency Utilities).

3. According to slide:
   BlockingQueue can solve Producer-Consumer problem
   without using wait(), notify(), notifyAll().

4. queue.put():
   - inserts element into queue
   - if queue is FULL → thread automatically waits

5. queue.take():
   - removes element from queue
   - if queue is EMPTY → thread automatically waits

6. So:
   ❌ No need for manual synchronization
   ❌ No need for wait/notify
   ✅ BlockingQueue handles everything internally

7. ArrayBlockingQueue(1):
   - capacity = 1
   - acts like single-slot buffer (classic PC problem)

8. Producer:
   - continuously produces values
   - blocks when queue is full

9. Consumer:
   - continuously consumes values
   - blocks when queue is empty

10. Advantage over previous methods:
    - simpler code
    - less error-prone
    - no deadlock risk (if used properly)

11. This replaces:
    Polling → IncorrectPC → CorrectPC

    Final evolution:
    BlockingQueue (BEST approach)

12. Slide connection:
    Concurrent Collections → BlockingQueue solves Producer-Consumer.
*/
