public class Ex1_GenObject {
    private Object a;

    public void setObj(Object a) {
        this.a = a;
    }

    public Object getObj() {
        return this.a;
    }

    public static void main(String[] args) {
        Ex1_GenObject obj = new Ex1_GenObject();

        obj.setObj("Hello");
        obj.setObj(10);
        obj.setObj(new Thread());

        System.out.println(obj.getObj());

        String s = (String) obj.getObj(); // risky casting
        System.out.println(s);
    }
}

/*
Key Notes:

1. Uses Object → can store ANY type (String, Integer, Thread).
2. Each new setObj() overwrites previous value.
3. getObj() returns Object → requires explicit casting.
4. Casting is risky → may cause runtime error (ClassCastException).
5. This is pre-generics approach → NOT type-safe.
*/