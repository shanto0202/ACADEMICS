//package generics;

// Generic class with bounded type (only Number or subclasses)
class Ex7_Stats<T extends Number> {

    T[] nums;

    // Constructor
    Ex7_Stats(T[] o) {
        nums = o;
    }

    // Calculate average
    double average() {
        double sum = 0.0;

        for (int i = 0; i < nums.length; i++) {
            sum += nums[i].doubleValue();
        }

        return sum / nums.length;
    }

    // Compare SAME type only
    boolean sameAvg(Ex7_Stats<T> obj) {
        if (average() == obj.average()) {
            return true;
        } else {
            return false;
        }
    }

    // Compare ANY type using wildcard
    boolean sameAvgAny(Ex7_Stats<?> obj) {
        if (average() == obj.average()) {
            return true;
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        Integer[] n1 = {10, 20, 30, 40, 50};
        Ex7_Stats<Integer> s1 = new Ex7_Stats<>(n1);
        System.out.println(s1.average());
        Integer[] n2 = {50, 20, 40, 10, 30};
        Ex7_Stats<Integer> s2 = new Ex7_Stats<>(n2);
        System.out.println(s2.average());

        System.out.println(s1.sameAvg(s2));
        Double[] n3 = {50.0, 40.0, 30.0, 20.0, 10.0};
        Ex7_Stats<Double> s3 = new Ex7_Stats<>(n3);
        System.out.println(s3.average());
        
        //System.out.println(s2.sameAvg(s3)); // error
        System.out.println(s2.sameAvgAny(s3));
    }
}


/*
Key Notes:

1. <?> = wildcard → unknown type
2. sameAvg() → only SAME type allowed
3. sameAvgAny() → ANY type allowed
4. Important:
   Ex7_Stats<Integer> ≠ Ex7_Stats<Double>
 */
