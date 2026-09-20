
class PrimeCounter implements Runnable {

    int[] numbers;
    int start, end;

    static long total = 0; //static
    Thread t;

    public PrimeCounter(int[] numbers, int start, int end) {
        this.numbers = numbers;
        this.start = start;
        this.end = end;
        t = new Thread(this);
        t.start();
    }

    public void run() {
        long localCount = 0;
        for (int i = start; i < end; i++) {
            if (isPrime(numbers[i])) {
                localCount++;
            }
        }
        synchronized (PrimeCounter.class) {
            total += localCount;
        }
    }

    private boolean isPrime(int n) {
        if (n <= 1) {
            return false;
        }
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
}

public class Ex10_Primecheck {

    public static void main(String[] args) {
        java.util.Random random = new java.util.Random();
        int[] numbers = new int[10000];
        // Generate random numbers between 1 and 5000
        for (int i = 0; i < numbers.length; i++) {
            numbers[i] = random.nextInt(5000) + 1;
        }
        PrimeCounter[] threads = new PrimeCounter[5];
        int part = numbers.length / 5;
        // Create 5 threads
        for (int i = 0; i < 5; i++) {
            int start = i * part;
            int end = (i == 4) ? numbers.length : start + part;
            threads[i] = new PrimeCounter(numbers, start, end);
        }
        //int totalPrimeCount = 0;
        // Wait for all threads
        for (int i = 0; i < 5; i++) {
            try {
                threads[i].t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            //totalPrimeCount += threads[i].localCount;
        }
        System.out.println("Total Prime Count = " + PrimeCounter.total);
    }
}
