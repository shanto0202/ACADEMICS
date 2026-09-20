//package synchronization;

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
        for (int i = 1; i <= 10; i++) {
            list.add(String.valueOf(i));
            // synchronized (list) {
            //     list.add(String.valueOf(i));
            // }
        }
    }
}

public class Ex5_TestSyncArrayList {

    public static void main(String[] args) {
        List<String> list = new ArrayList<>();
        MyThread myThread1 = new MyThread(list);
        MyThread myThread2 = new MyThread(list);
        try {
            myThread1.t.join();
            myThread2.t.join();
        } catch (Exception e) {
            System.out.println(e);
        }
        // for (int i = 0; i < list.size(); i++) {
        //     System.out.println(list.get(i));
        // }
        System.out.println(list.size());
    }
}
