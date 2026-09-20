// Superclass reference to subclass object

class Box {

    double width;
    double height;
    double depth;

    Box(double w, double h, double d) {

        width = w;
        height = h;
        depth = d;
    }

    double volume() {

        return width * height * depth;
    }
}

class BoxWeight extends Box {

    double weight;

    BoxWeight(double w, double h, double d, double m) {

        super(w, h, d);

        weight = m;
    }
}

public class Ex7_SuperclassReference {

    public static void main(String[] args) {

        BoxWeight weightBox = new BoxWeight(3, 5, 7, 8.37);

        System.out.println("Weight: " + weightBox.weight);

        // superclass reference → subclass object
        Box plainBox = weightBox;

        // OK → volume() exists in Box
        System.out.println("Volume: " + plainBox.volume());

        /*
        Error:
        weight not defined in Box

        System.out.println(plainBox.weight);
        */

        Box box = new Box(1, 2, 3);

        // OK
        box = weightBox;

        /*
        Error:
        can't assign superclass object
        to subclass reference

        BoxWeight wbox = box;
        */
    }
}

/*
Key Notes
---------
Superclass reference can refer to subclass object.

Example:
Box plainBox = weightBox;

This is called:
Upcasting

Using superclass reference:
✔ Can access superclass members.
✘ Cannot access subclass-specific members.

Invalid:
BoxWeight wbox = box;

Because superclass object may not contain
subclass members.
*/