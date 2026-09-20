//package advanced;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class MyRunnable implements Runnable {

    public void run() {
        System.out.println("Running task");
        for (int j = 5; j > 0; j--) {
            System.out.println(j);
        }
    }
}

public class Ex6_ExecutorServiceTest {

    public static void main(String[] args) {
        ExecutorService executorService = Executors.newFixedThreadPool(10);
        for (int i = 0; i < 20; i++) {
            executorService.execute(new MyRunnable());
        }
        executorService.shutdown();
    }
}

/*
Key Notes:

1. This program demonstrates ExecutorService (modern thread management).

2. According to slide:
   Executor provides an alternative to managing threads
   instead of using Thread class directly.

3. Executors.newFixedThreadPool(10):
   - creates a thread pool of size 10
   - at most 10 threads will run concurrently
   - remaining tasks wait in queue

4. executorService.execute():
   - submits a task (Runnable) to the pool
   - thread pool assigns available thread automatically

5. Here:
   - 20 tasks are submitted
   - but only 10 run at a time
   - remaining tasks wait until threads are free

6. Advantages of thread pool:
   - avoids overhead of creating new thread repeatedly
   - better performance
   - better resource management (memory + CPU)

7. executorService.shutdown():
   - stops accepting new tasks
   - previously submitted tasks will complete

8. Important concept:
   ExecutorService extends Executor
   and provides control over thread lifecycle.

9. This is part of Java Concurrency Utilities:
   java.util.concurrent package.

10. Slide concept:
    Executor → controls execution of threads
    Thread Pool → reuse threads instead of creating new ones
*/
