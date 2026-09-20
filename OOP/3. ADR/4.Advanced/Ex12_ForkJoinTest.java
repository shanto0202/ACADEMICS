//package advanced;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.RecursiveTask;

class CustomRecursiveAction extends RecursiveAction {

    private String workload = "";
    private static final int THRESHOLD = 4;

    public CustomRecursiveAction(String workload) {
        this.workload = workload;
    }

    @Override
    protected void compute() {
        if (workload.length() > THRESHOLD) {
            invokeAll(createSubtasks());
        } else {
            processing(workload);
        }
    }

    private List<CustomRecursiveAction> createSubtasks() {
        List<CustomRecursiveAction> subTasks = new ArrayList<>();

        String partOne = workload.substring(0, workload.length() / 2);
        String partTwo = workload.substring(workload.length() / 2, workload.length());

        subTasks.add(new CustomRecursiveAction(partOne));
        subTasks.add(new CustomRecursiveAction(partTwo));

        return subTasks;
    }

    private void processing(String work) {
        String result = work.toUpperCase();
        System.out.println("This result - (" + result + ") - was processed by "+ Thread.currentThread().getName());
    }
}

class CustomRecursiveTask extends RecursiveTask<Integer> {

    private int[] arr;
    private static final int THRESHOLD = 20;

    public CustomRecursiveTask(int[] arr) {
        this.arr = arr;
    }

    @Override
    protected Integer compute() {
        int sum = 0;
        if (arr.length > THRESHOLD) {
            CustomRecursiveTask customRecursiveTaskA = new CustomRecursiveTask(
                    Arrays.copyOfRange(arr, 0, arr.length / 2));
            CustomRecursiveTask customRecursiveTaskB = new CustomRecursiveTask(
                    Arrays.copyOfRange(arr, arr.length / 2, arr.length));
            customRecursiveTaskA.fork();
            customRecursiveTaskB.fork();
            sum = customRecursiveTaskA.join() + customRecursiveTaskB.join();
            return sum;
        } else {
            return processing(arr);
        }
    }

    private Integer processing(int[] arr) {
        int sum = 0;
        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];
        }
        System.out.println("This result - (" + sum + ") - was processed by "
                + Thread.currentThread().getName());
        return sum;
    }
}

public class Ex12_ForkJoinTest {

    public static void main(String[] args) {
        /*
         * String alphabet =
         * "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
         * CustomRecursiveAction customRecursiveAction = new
         * CustomRecursiveAction(alphabet);
         * ForkJoinPool forkJoinPool = ForkJoinPool.commonPool();
         * forkJoinPool.invoke(customRecursiveAction);
         */

        int[] a = new int[10000];
        for (int i = 0; i < a.length; i++) {
            a[i] = 10;
        }
        CustomRecursiveTask customRecursiveTask = new CustomRecursiveTask(a);
        ForkJoinPool forkJoinPool = ForkJoinPool.commonPool();
        System.out.println(forkJoinPool.invoke(customRecursiveTask));
    }
}

/*
Key Notes:

1. This program demonstrates the Fork/Join Framework.

2. According to slide:
   Fork/Join is used for parallel programming
   and utilizes multiple processors efficiently.

3. Core idea:
   Divide and Conquer approach.

   - Break large task into smaller subtasks (fork)
   - Process them in parallel
   - Combine results (join)

----------------------------------------
PART 1: RecursiveAction (no return value)
----------------------------------------

4. CustomRecursiveAction extends RecursiveAction:
   - used when task does NOT return result

5. compute():
   - if workload is large → split into subtasks
   - if small → process directly

6. invokeAll():
   - runs subtasks in parallel

7. THRESHOLD:
   - controls when to split vs process
   - very important tuning parameter

----------------------------------------
PART 2: RecursiveTask (returns value)
----------------------------------------

8. CustomRecursiveTask extends RecursiveTask<Integer>:
   - used when task returns result

9. compute():
   - if array is large → split into two parts
   - fork() → submit subtask asynchronously
   - join() → wait and get result
   - combine results

10. processing():
    - calculates sum of array
    - runs when task size is small

----------------------------------------
PART 3: ForkJoinPool
----------------------------------------

11. ForkJoinPool:
    - manages worker threads
    - executes fork/join tasks

12. commonPool():
    - shared pool provided by Java

13. forkJoinPool.invoke(task):
    - starts execution
    - returns final result

----------------------------------------
IMPORTANT CONCEPTS (Exam Focus)
----------------------------------------

14. fork():
    - splits task and executes asynchronously

15. join():
    - waits and retrieves result

16. RecursiveTask vs RecursiveAction:
    - RecursiveTask → returns result
    - RecursiveAction → no return

17. Benefits:
    - automatic parallelism
    - better CPU utilization
    - scalable with number of processors

----------------------------------------
SLIDE CONNECTION
----------------------------------------

18. Slide topic:
    Fork/Join Framework → simplifies multithreading
    supports parallel processing using divide-and-conquer.
*/