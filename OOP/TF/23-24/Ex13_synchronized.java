
import java.util.ArrayList;
import java.util.List;

class MyThread implements Runnable {

    List<String> list;
    Thread t;

    public MyThread(List<String> list) {
        this.list = list;
        t = new Thread(this);
        t.start();
    }

    public void run() {
        for (int i = 1; i <= 10000; i++) {
            synchronized (MyThread.class) {
                list.add(String.valueOf(i));
            }
        }
    }
}

public class Ex13_synchronized {

    public static void main(String[] args) throws Exception {

        // List<String> list = Collections.synchronizedList(new ArrayList<>());
        List<String> list = new ArrayList<>();

        MyThread myThread1 = new MyThread(list);
        MyThread myThread2 = new MyThread(list);

        try {
            myThread1.t.join();
            myThread2.t.join();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        System.out.println(list.size()); // 20000
    }
}

/*
Key Notes:

1. ArrayList is not thread-safe.
2. Two threads adding at same time causes race condition.
3. Collections.synchronizedList(...) makes list thread-safe.
4. join() ensures main waits for both threads to finish.
5. Final size becomes correct: 20000
 */
