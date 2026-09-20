// An enumeration of apple varieties

enum Apple {
    Jonathan, GoldenDel, RedDel, Winesap, Cortland
}

public class Ex1_EnumDemo {

    public static void main(String args[]) {

        Apple ap;

        ap = Apple.RedDel;

        // print enum value
        System.out.println("Value of ap: " + ap);
        //System.out.println();

        ap = Apple.GoldenDel;

        // comparison
        if (ap == Apple.GoldenDel) {
            System.out.println("ap contains GoldenDel.\n");
        }

        // switch with enum
        switch (ap) {
            case Jonathan:
                System.out.println("Jonathan is red.");
                break;
            case GoldenDel:
                System.out.println("Golden Delicious is yellow.");
                break;
            case RedDel:
                System.out.println("Red Delicious is red.");
                break;
            case Winesap:
                System.out.println("Winesap is red.");
                break;
            case Cortland:
                System.out.println("Cortland is red.");
                break;
        }
    }
}

/*
Key Notes:

1. enum = collection of named constants.
2. Enum is actually a class type in Java.
3. Use == for comparison (safe).
4. Works perfectly with switch-case.
5. Each constant is an object of enum type.
*/
