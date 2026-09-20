
class Ex8 {

    public static void main(String[] args) {

        String s1 = "Hello";
        String s2 = new String("Hello");
        String s3 = "Hello";

        s2.intern();

        System.out.println(s1 == s2); // false
        System.out.println(s1 == s3); // true
        System.out.println(s2 == s3); // false

        final String s0 = "Hello";
        final String t0 = "World";

        String t1 = s0 + t0;
        String t2 = new String("HelloWorld");
        String t3 = "HelloWorld";

        t3.intern();

        System.out.println(t1 == t2); // false
        System.out.println(t1 == t3); // true
        System.out.println(t2 == t3); // false

        //Efficient rewrite of string concatenation in loop
        StringBuilder result = new StringBuilder();

        for (int i = 0; i < 10000; i++) {
            result.append(i);
        }

        System.out.println(result.toString());
    }
}

/*
Key Notes:

1. String pool:
   - String literals are stored in string constant pool
   - same literal usually points to same object

2. new String("Hello"):
   - creates a new object in heap
   - so s2 is different from s1 and s3

3. == operator:
   - compares references
   - not content

4. s1 == s2:
   - false
   - because s2 is created with new

5. s1 == s3:
   - true
   - both refer to same pooled literal "Hello"

6. s2 == s3:
   - false
   - heap object vs pool object

7. intern():
   - returns pooled reference of that string
   - it does NOT change the original reference unless assigned back
   - so s2.intern(); alone does not make s2 point to pool

8. final String s0 = "Hello";
   final String t0 = "World";
   - both are constants
   - so s0 + t0 is compile-time constant
   - t1 becomes pooled "HelloWorld"

9. t2 = new String("HelloWorld"):
   - creates separate heap object

10. t3 = "HelloWorld":
    - pooled literal

11. t1 == t2:
    - false

12. t1 == t3:
    - true
    - both point to pooled "HelloWorld"

13. t2 == t3:
    - false

14. Problem with:
       String result = "";
       for (...) {
           result += i;
       }
    - String is immutable
    - every + creates a new String object
    - very inefficient in loop

15. Efficient rewrite:
    - use StringBuilder when only one thread is used
    - StringBuffer is synchronized, so slower
    - StringBuilder is faster for single-thread use

16. Final outputs:
    false
    true
    false
    false
    true
    false
*/
