public class Ex9_va_list_not_in_the_slide {

    static int maxmin(String s, int... a) {
        int res = a[0];
        for (int i = 1; i < a.length; i++) {
            if (s.equals("min")) {
                if (a[i] < res) {
                    res = a[i];
                }
            } else if (s.equals("max")) {
                if (a[i] > res) {
                    res = a[i];
                }
            }
        }
        return res;
    }

    public static void main(String[] args) {

        int minVal = maxmin("min", 5, 3, 9, 1, 7);
        int maxVal = maxmin("max", 5, 3, 9, 1, 7);

        System.out.println("Minimum: " + minVal);
        System.out.println("Maximum: " + maxVal);
    }
}
