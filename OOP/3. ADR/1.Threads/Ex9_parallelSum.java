
class ParallelSum implements Runnable {
    int[] numbers;
    int start, end;
    static long totalSum = 0;   // shared variable
    Thread t;
    public ParallelSum(int[] numbers, int start, int end) {
        this.numbers = numbers;
        this.start = start;
        this.end = end;
        t = new Thread(this);
        t.start();
    }
    public void run() {
        long localSum = 0;

        for (int i = start; i < end; i++) {
            localSum += numbers[i];
        }
        // synchronized block to update shared total
        synchronized (ParallelSum.class) {
            totalSum += localSum;
        }
        // 3=100, localsum==50, total sum=150
        // 4=150, localsum=60, total sum=210
    }
}
public class Ex9_parallelSum {
    public static void main(String[] args) {
        java.util.Random random = new java.util.Random();
        int[] numbers = new int[10000];
        for (int i = 0; i < numbers.length; i++) {
            numbers[i] = random.nextInt(10000);
        }
        ParallelSum[] parallelSum = new ParallelSum[10];
        int part = numbers.length / 10;
        
        // Create 10 threads
        for (int i = 0; i < 10; i++) {
            int start = i * part;
            int end = (i == 9) ? numbers.length : start + part;
            parallelSum[i] = new ParallelSum(numbers, start, end);
        }
        // Wait for all threads
        for (int i = 0; i < 10; i++) {
            try {
                parallelSum[i].t.join();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        System.out.println("Total Sum = " + ParallelSum.totalSum);
    }
}
