//package advanced;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

class P implements Runnable {

    private final BlockingQueue<Integer> queue;
    private final Integer POISON;

    @Override
    public void run() {

        try {
            process();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } finally {
            while (true) {
                try {
                    queue.put(POISON);
                    queue.put(POISON);
                    break;
                } catch (InterruptedException e) {
                    // ...
                }
            }
        }

    }

    private void process() throws InterruptedException {

        // Put 20 elements into Queue
        for (int i = 0; i < 20; i++) {
            System.out.println("[Producer] Put : " + i);
            queue.put(i);
            System.out.println("[Producer] Queue remainingCapacity : " + queue.remainingCapacity());
            Thread.sleep(100);
        }

    }

    public P(BlockingQueue<Integer> queue, Integer POISON) {
        this.queue = queue;
        this.POISON = POISON;
    }

}

class C implements Runnable {

    private final BlockingQueue<Integer> queue;
    private final Integer POISON;

    @Override
    public void run() {

        try {
            while (true) {
                Integer take = queue.take();
                process(take);

                // if this is a poison pill, break, exit
                if (take == POISON) {
                    break;
                }

            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

    }

    private void process(Integer take) throws InterruptedException {
        System.out.println("[Consumer] Take : " + take);
        Thread.sleep(500);
    }

    public C(BlockingQueue<Integer> queue, Integer POISON) {
        this.queue = queue;
        this.POISON = POISON;
    }
}

public class Ex10_Main {

    public static void main(String[] args) {
        BlockingQueue<Integer> queue = new LinkedBlockingQueue<>(1);

        // new Thread(new Producer(queue)).start();
        // new Thread(new Consumer(queue)).start();
        Integer poison = -1;
        new Thread(new P(queue, poison)).start();
        // new Thread(new advanced.P(queue, poison)).start();

        new Thread(new C(queue, poison)).start();
        new Thread(new C(queue, poison)).start();
    }
}

/*
Key Notes:

1. This is an advanced Producer-Consumer example using BlockingQueue.

2. It uses LinkedBlockingQueue, which is also part of
   java.util.concurrent package.

3. Like previous BlockingQueue example:
   - queue.put() waits automatically if queue is full
   - queue.take() waits automatically if queue is empty
   - no need for wait(), notify(), notifyAll()

4. Special idea used here:
   POISON PILL technique.

5. What is poison pill?
   - a special marker value inserted into queue
   - signals consumers that production is finished
   - after reading poison pill, consumer stops

6. Here:
   - producer puts values 0 to 19
   - after finishing, it inserts POISON twice
   - because there are 2 consumer threads
   - each consumer needs one poison pill to terminate

7. Why finally block is used?
   - ensures poison pills are inserted
   - even if interruption happens during processing

8. Consumer logic:
   - take item from queue
   - process it
   - if item is poison pill, break loop and exit

9. Important concept:
   This example solves graceful thread termination.
   In many producer-consumer systems,
   stopping threads safely is a major issue.

10. remainingCapacity():
    - shows how much space is left in queue

11. VERY IMPORTANT note:
    In this line:
    if (take == POISON)

    safer comparison is:
    if (take.equals(POISON))

    because Integer is an object, and equals() checks value.
    == checks reference.

12. This code is related to slide topic:
    Concurrent Collections → BlockingQueue for Producer-Consumer.
    It is an extended practical version of that concept.
*/
