//package advanced;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

class MyCallable implements Callable<Integer> {

    @Override
    public Integer call() {
        int sum = 0;
        for (int i = 1; i <= 10; i++) {
            sum += i;
        }
        return sum;
    }
}

public class Ex7_CallableFutures {

    public static void main(String[] args) throws Exception {
        ExecutorService executor = Executors.newFixedThreadPool(10);
        List<Future<Integer>> futureList = new ArrayList<>();
        for (int i = 0; i < 20; i++) {
            Future<Integer> submit = executor.submit(new MyCallable());
            futureList.add(submit);
        }
        executor.shutdown();
        int sum = 0;
        // Now retrieve the result
        for (Future<Integer> future : futureList) {
            sum += future.get();
        }
        System.out.println(sum);
    }
}

/*
Key Notes:

1. This program demonstrates Callable and Future.

2. Difference from Runnable:
   - Runnable → does NOT return result
   - Callable → returns result using call()

3. MyCallable implements Callable<Integer>:
   - call() method returns an Integer
   - here it calculates sum from 1 to 10

4. executor.submit():
   - submits Callable task
   - returns Future object

5. Future:
   - represents result of asynchronous computation
   - acts like a placeholder for result

6. future.get():
   - returns actual result
   - blocks (waits) until computation is complete

7. Here:
   - 20 tasks are submitted
   - each returns sum = 55
   - total sum = 20 × 55 = 1100

8. ExecutorService is used to manage threads:
   - fixed thread pool of 10 threads

9. Important methods of Future (from slide):
   - get() → get result (blocking)
   - isDone() → check if completed
   - cancel() → cancel task

10. Key concept:
    Callable + Future enables returning values from threads.

11. Slide connection:
    "Callable and Future" → allows returning result after execution.
*/