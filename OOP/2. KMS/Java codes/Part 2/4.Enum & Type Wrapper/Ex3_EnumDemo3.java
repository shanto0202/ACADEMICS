// enum with constructor, variable, method

enum AppleNew {
    Jonathan(10), GoldenDel(9),
    RedDel(12), Winesap(15), Cortland(8);

    private int price;

    // constructor
    AppleNew(int p) {
        price = p;
        //System.out.println("Ifat");
    }

    int getPrice() {
        return price;
    }

    void setPrice(int price) {
        this.price = price;
    }

    @Override
    public String toString() {
        return "AppleNew{price=" + price + '}';
    }
}

public class Ex3_EnumDemo3 {

    public static void print(AppleNew a) {
        System.out.println(a);
    }

    public static void main(String args[]) {

        System.out.println("Winesap costs "+ AppleNew.Winesap.getPrice() + " cents.\n");

        System.out.println("All apple prices:");

        for (AppleNew a : AppleNew.values()) {
            System.out.println(a + " costs " + a.getPrice() + " cents.");
        }

        System.out.println(AppleNew.Winesap.getPrice());

        AppleNew.Winesap.setPrice(100);

        System.out.println(AppleNew.Winesap.getPrice());

        print(AppleNew.Winesap);
    }
}

/*
Key Notes:

1. Enum can have:
   - constructor
   - variables
   - methods
2. Each constant is an object → Jonathan, Winesap etc.
3. Constructor runs for each constant.
4. You can store data inside enum (VERY IMPORTANT).
5. Used in real-world → status, type, config.
*/