//package advanced;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Ex8_CallableFutures2 {

    public static void main(String[] args) throws Exception {
        ExecutorService executor = Executors.newFixedThreadPool(10);
        List<Callable<Integer>> taskList = new ArrayList<>();
        for (int i = 0; i < 20; i++) {
            taskList.add(new MyCallable());
        }
        List<Future<Integer>> futureList = executor.invokeAll(taskList);
        int sum = 0;
        // Now retrieve the result
        for (Future<Integer> future : futureList) {
            sum += future.get();
        }
        System.out.println(sum);
        executor.shutdown();
    }
}

/*
Key Notes:

1. This program also demonstrates Callable and Future,
   but uses invokeAll() instead of submit().

2. Difference from previous example:
   - submit() → submit tasks one by one
   - invokeAll() → submits ALL tasks together as a collection

3. taskList:
   - contains 20 Callable tasks
   - each task is MyCallable (returns sum = 55)

4. executor.invokeAll(taskList):
   - executes all tasks
   - returns List<Future>
   - waits until ALL tasks are completed

5. Important behavior:
   invokeAll() is blocking → it does NOT return until all tasks finish

6. future.get():
   - retrieves result of each task
   - no extra waiting needed usually (already completed)

7. Total result:
   - each task → 55
   - 20 tasks → 1100

8. Advantage of invokeAll():
   - simpler when handling batch tasks
   - no need to manually collect futures one by one

9. ExecutorService is still used:
   - manages thread pool
   - improves performance

10. Slide concept:
    Callable + Future → return results from threads
    invokeAll() → batch execution of tasks
*/
