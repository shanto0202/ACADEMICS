
class OrderStatusOld {

    public static final int PENDING = 0;
    public static final int SHIPPED = 1;
    public static final int DELIVERED = 2;
}

enum OrderStatus {
    PENDING, SHIPPED, DELIVERED
}

public class Ex4_FinalVsEnum {

    static void printStatusOld(int status) {
        if (status == OrderStatusOld.PENDING) {
            System.out.println("Pending");
        } else if (status == OrderStatusOld.SHIPPED) {
            System.out.println("Shipped");
        } else if (status == OrderStatusOld.DELIVERED) {
            System.out.println("Delivered");
        } else {
            System.out.println("Nothing.");
        }
    }

    static void printStatus(OrderStatus status) {
        switch (status) {
            case PENDING ->
                System.out.println("Pending");
            case SHIPPED ->
                System.out.println("Shipped");
            case DELIVERED ->
                System.out.println("Delivered");
        }
    }

    public static void main(String[] args) {

        printStatusOld(1);   // unclear
        printStatusOld(100); // compiles but wrong

        printStatus(OrderStatus.SHIPPED); // safe
    }
}

/*
Key Notes:

1. final constants → not type-safe.
2. Enum → type-safe (compile-time checking).
3. Enum prevents invalid values.
4. Enum improves readability.
5. VERY IMPORTANT exam comparison.
 */
