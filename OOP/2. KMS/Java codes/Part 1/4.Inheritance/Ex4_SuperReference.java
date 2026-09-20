// Superclass reference to subclass object

class Box2 {

    double width, height, depth;

    Box2(double w, double h, double d) {
        width = w;
        height = h;
        depth = d;
    }

    double volume() {
        return width * height * depth;
    }
}

class BoxWeight2 extends Box2 {

    double weight;

    BoxWeight2(double w, double h, double d, double m) {
        super(w, h, d);
        // super.width=w;
        weight = m;
    }
}

public class Ex4_SuperReference {

    public static void main(String[] args) {

        BoxWeight2 weightBox = new BoxWeight2(3, 5, 7, 8.37);
        System.out.println(weightBox.weight);

        Box2 plainBox = weightBox;
        System.out.println(plainBox.volume());

    }
}

/*
Key Notes
---------
Superclass reference can refer to subclass object.

But it can only access superclass members.
 */
