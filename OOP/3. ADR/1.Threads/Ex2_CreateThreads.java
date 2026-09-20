//package threads;

public class Ex2_CreateThreads {

    public void f1() {
        for (int i = 10; i > 0; i--) {
            System.out.println("f1(): " + i);
            try {
                Thread.sleep(200);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
    }

    public static void f2() {
        for (int i = 10; i > 0; i--) {
            System.out.println("f2(): " + i);
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
    }

    public static void main(String[] args) {
        Ex2_CreateThreads ct = new Ex2_CreateThreads();
        //new Thread("T0").start();
        new Thread(ct::f1, "T1").start();
        new Thread(Ex2_CreateThreads::f2, "T2").start(); //if static, no object needed
    }

}
