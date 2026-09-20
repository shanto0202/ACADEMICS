
class Box {

    private double length, width, height;

    public Box(double length, double width, double height) {
        this.length = length;
        this.width = width;
        this.height = height;
    }

    public Box(Box ob) {
        this(ob.length, ob.width, ob.height);
    }

    public double volume() {
        return length * width * height;
    }
}
