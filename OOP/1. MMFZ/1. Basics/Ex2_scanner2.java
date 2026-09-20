import java.util.Scanner;

public class Ex2_scanner2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String s = sc.nextLine(); // full line with spaces
        String w = sc.next(); // single word
        int i = sc.nextInt(); // integer: -2B to 2B
        double d = sc.nextDouble(); // decimal: 15-16 digits precision
        float f = sc.nextFloat(); // decimal: 6-7 digits precision
        long l = sc.nextLong(); // big integer: -9Q to 9Q
        short sh = sc.nextShort(); // small int: -32768 to 32767
        byte b = sc.nextByte(); // tiny int: -128 to 127
        boolean bool = sc.nextBoolean(); // true or false

        System.out.print(s + " " + w + " " + i + " " + d + " " + f + " " + l + " " + sh + " " + b + " " + bool);

        sc.close();
    }
}
