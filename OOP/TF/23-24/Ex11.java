
class MyMax<T extends Number> {

    private T[] nums;

    // Constructor
    public MyMax(T[] nums) {
        this.nums = nums;
    }

    // Find maximum value
    public double max() {
        double mx = nums[0].doubleValue();

        for (int i = 1; i < nums.length; i++) {
            if (nums[i].doubleValue() > mx) {
                mx = nums[i].doubleValue();
            }
        }
        return mx;
    }

    // Compare with SAME generic type only
    public boolean sameMax1(MyMax<T> other) {
        return this.max() == other.max();
    }

    // Compare with ANY numeric generic type
    public boolean sameMax2(MyMax<?> other) {
        return this.max() == other.max();
    }
}

public class Ex11 {

    public static void main(String[] args) {

        Long[] n1 = {10L, 20L, 30L, 40L, 50L};
        MyMax<Long> mx1 = new MyMax<>(n1);
        System.out.println(mx1.max());

        Float[] n2 = {50.0f, 20.0f, 40.0f, 10.0f, 30.0f};
        MyMax<Float> mx2 = new MyMax<>(n2);
        System.out.println(mx2.max());

        Double[] n3 = {50.0, 20.0, 40.0, 10.0, 30.0};
        MyMax<Double> mx3 = new MyMax<>(n3);
        System.out.println(mx3.max());

        System.out.println(mx1.sameMax2(mx2)); // true
        System.out.println(mx2.sameMax2(mx3)); // true
    }
}

/*
Key Notes:

1. T extends Number:
   - MyMax can only be created for number types
   - like Integer, Long, Float, Double
   - cannot use String

2. Why extends Number?
   - Number class gives methods like:
     doubleValue(), intValue(), floatValue()

3. max():
   - finds largest element in array
   - converts every number to double for comparison

4. sameMax1(MyMax<T> other):
   - compares only SAME generic type
   - example:
       MyMax<Long> with MyMax<Long> -> allowed
       MyMax<Long> with MyMax<Float> -> not allowed

5. sameMax2(MyMax<?> other):
   - wildcard version
   - compares with ANY generic type
   - example:
       MyMax<Long> with MyMax<Float> -> allowed

6. In this question:
   - mx1.max() = 50.0
   - mx2.max() = 50.0
   - mx3.max() = 50.0
   - so both comparisons return true

7. Main restriction satisfied:
   - only Java number classes allowed
   - sameMax1 and sameMax2 implemented differently
*/
