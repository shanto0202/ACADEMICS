public class reference {  // Class name changed to Demo
    int L, W, H;

    reference(int l, int w, int h) { // Constructor changed to Demo
        L = l; 
        W = w; 
        H = h;
    }

    @Override
    public String toString() {
        return "(" + L + ", " + W + ", " + H + ")";
    }

    public static void main(String[] args) {
        reference b1;  
        reference b2;

        b1 = new reference(8, 5, 7); 
        System.out.println("b1: " + b1);

        b2 = b1; 
        System.out.println("b2 points to b1's object: " + b2);
    }
}