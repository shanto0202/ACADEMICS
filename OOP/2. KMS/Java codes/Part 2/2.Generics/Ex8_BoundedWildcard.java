//package generics;

// Base class
class TwoD {

    int x, y;

    TwoD(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

// Derived class
class ThreeD extends TwoD {

    int z;

    ThreeD(int x, int y, int z) {
        super(x, y);
        this.z = z;
    }
}

// Further derived
class FourD extends ThreeD {

    int t;

    FourD(int x, int y, int z, int t) {
        super(x, y, z);
        this.t = t;
    }
}

// Generic container
class Coords<T extends TwoD> {

    T[] coords;

    Coords(T[] o) {
        coords = o;
    }
}

// Bounded wildcard class
class Ex8_BoundedWildcard {

    // Works for ALL types
    static void showXY(Coords<?> c) {
        for (int i = 0; i < c.coords.length; i++) {
            System.out.println(c.coords[i].x + " " + c.coords[i].y);
        }
    }

    // Only ThreeD and subclasses
    static void showXYZ(Coords<? extends ThreeD> c) {
        for (int i = 0; i < c.coords.length; i++) {
            System.out.println(c.coords[i].x + " " + c.coords[i].y + " " + c.coords[i].z);
        }
    }

    // Only FourD
    static void showAll(Coords<? extends FourD> c) {
        for (int i = 0; i < c.coords.length; i++) {
            System.out.println(c.coords[i].x + " " + c.coords[i].y + " " + c.coords[i].z + " " + c.coords[i].t);
        }
    }

    public static void main(String[] args) {

        TwoD[] twoD = {
            new TwoD(1, 8),
            new TwoD(2, 7),
            new TwoD(3, 6),
            new TwoD(4, 5)
        };

        Coords<TwoD> twoDCoords = new Coords<>(twoD);

        Ex8_BoundedWildcard.showXY(twoDCoords);

        // ❌ ERROR (no z)
        // Ex8_BoundedWildcard.showXYZ(twoDCoords);
        FourD[] fourD = {
            new FourD(1, 8, 9, 16),
            new FourD(2, 7, 10, 15),
            new FourD(3, 6, 11, 14),
            new FourD(4, 5, 12, 13)
        };

        Coords<FourD> fourDCoords = new Coords<>(fourD);

        Ex8_BoundedWildcard.showXY(fourDCoords);
        Ex8_BoundedWildcard.showXYZ(fourDCoords);
        Ex8_BoundedWildcard.showAll(fourDCoords);
    }
}

/*
Key Notes:

1. <? extends X> = upper bound
2. Allows X + subclasses
3. Hierarchy:
   TwoD → ThreeD → FourD

1. showXY → works for all
2. showXYZ → needs z → ThreeD+
3. showAll → needs t → FourD only

Exam trap:
Method depends on available fields
 */
