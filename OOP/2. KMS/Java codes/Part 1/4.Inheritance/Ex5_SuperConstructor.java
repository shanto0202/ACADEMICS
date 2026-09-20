// Using super to call superclass constructor

class Box3 {
    double width, height, depth;

    Box3(double w, double h, double d) {
        width = w;
        height = h;
        depth = d;
    }

    Box3(double len) {
        width = height = depth = len;
    }

    Box3() {
        width = height = depth = 0;
    }
}

class BoxWeight3 extends Box3 {
    double weight;

    BoxWeight3(double w, double h, double d, double m) {
        super(w, h, d);
        weight = m;
    }

    BoxWeight3(double len, double m) {
        super(len);
        weight = m;
    }

    BoxWeight3() {
        super();
        weight = 1;
    }
}

public class Ex5_SuperConstructor {

    public static void main(String[] args) {

        BoxWeight3 box1 = new BoxWeight3(10,20,15,34.3);
        BoxWeight3 box2 = new BoxWeight3(3,2);

        System.out.println(box1.weight);
        System.out.println(box2.weight);

    }
}

/*
Key Notes
---------
super() calls superclass constructor.

Must be FIRST statement in subclass constructor.
*/
