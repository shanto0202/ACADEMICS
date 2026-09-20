
class Box {

    double length;
    double width;
    double height;

    // Constructor
    Box(double l, double w, double h) {
        length = l;
        width = w;
        height = h;
    }

    // Copy constructor
    Box(Box ob) {  //Java does NOT have references like C++
        length = ob.length;
        width = ob.width;
        height = ob.height;
    }

    void setwidth(int w) {
        width = w;
    }

    double volume() {
        return length * width * height;
    }
}

public class Ex3_box {

    public static void main(String[] args) {

        Box myBox = new Box(5, 3, 2);
        Box myClone = new Box(myBox);

        // myBox.setwidth(0);
        
        System.out.println("Box Volume: " + myBox.volume());
        System.out.println("Clone Volume: " + myClone.volume());
    }
}
