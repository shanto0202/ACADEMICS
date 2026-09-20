//package advanced;

class A {

    synchronized void foo(B b) {
        String name = Thread.currentThread().getName();
        System.out.println(name + " entered advanced.A.foo");
        /*
         * try {
         * Thread.sleep(1000);
         * } catch (InterruptedException e) {
         * e.printStackTrace();
         * }
         */
        System.out.println(name + " trying to call advanced.B.last");
        b.last();
    }

    synchronized void last() {
        System.out.println("Inside advanced.A.last");
    }

}

class B {

    synchronized void bar(A a) {
        String name = Thread.currentThread().getName();
        System.out.println(name + " entered advanced.B.bar");
        /*
         * try {
         * Thread.sleep(1000);
         * } catch (InterruptedException e) {
         * e.printStackTrace();
         * }
         */
        System.out.println(name + " trying to call advanced.A.last");
        a.last();
    }

    synchronized void last() {
        System.out.println("Inside advanced.B.last");
    }
}

public class Ex4_Deadlock implements Runnable {

    A a;
    B b;
    Thread t;

    Ex4_Deadlock() {
        a = new A();
        b = new B();
        Thread.currentThread().setName("advanced.Main Thread");
        t = new Thread(this, "Racing Thread");
    }

    void deadlockStart() {
        t.start();
        a.foo(b);
        System.out.println("Back in advanced.Main Thread");
    }

    public void run() {
        b.bar(a);
        System.out.println("Back in Racing Thread");
    }

    public static void main(String[] args) {
        Ex4_Deadlock deadlock = new Ex4_Deadlock();
        deadlock.deadlockStart();
    }

}

/*
Key Notes:

1. This program demonstrates DEADLOCK.

2. Deadlock happens when:
   - Thread 1 holds lock on object A and waits for object B
   - Thread 2 holds lock on object B and waits for object A
   - both wait forever

3. In this code:
   - Main Thread enters a.foo(b)
     → gets lock of object A
     → then tries to call b.last()
     → needs lock of object B

   - Racing Thread enters b.bar(a)
     → gets lock of object B
     → then tries to call a.last()
     → needs lock of object A

4. So:
   - Main Thread waits for B
   - Racing Thread waits for A
   - circular dependency created
   - program gets stuck forever

5. This is exactly the condition described in the slide:
   circular dependency on synchronized objects.

6. synchronized methods mean:
   - foo() locks object A
   - bar() locks object B
   - last() also needs the corresponding object lock

7. Because locks are nested in opposite order,
   deadlock becomes possible.

8. Very important exam concept:
   Deadlock does NOT mean crash.
   It means program is blocked forever.

9. Slide idea:
   If a multithreaded program locks up occasionally,
   deadlock is one of the first things to check.

10. Uncommenting sleep() often makes deadlock easier to observe,
    because it increases timing chance between two threads.

11. This file directly matches the slide topic:
    Deadlock → circular dependency between two synchronized objects.
*/
