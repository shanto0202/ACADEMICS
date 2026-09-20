
interface Stack<T> {
    void push(T e);
    T pop();
    boolean isEmpty();
}

class MyStack<T> implements Stack<T> {
    T[] arr;
    int top = -1;

    MyStack(T[] arr) { 
        this.arr = arr;
    }

    public void push(T e) {
        arr[++top] = e;
    }

    public T pop() {
        return arr[top--];
    }

    public boolean isEmpty() {
        return top == -1;
    }
}

public class Ex6_GenericInterface {

    public static void main(String[] args) {
        String[] s = new String[10];
        MyStack<String> st = new MyStack<>(s);

        st.push("A");
        st.push("B");

        while (!st.isEmpty()) {
            System.out.println(st.pop());
        }
    }
}

/*
Key Notes:

1. Generic interface → Stack<T>.
2. MyStack<T> implements generic behavior.
3. Works for any type (String, Integer, etc).
4. Demonstrates reusable data structure.
5. Stack follows LIFO (Last In First Out).
*/
