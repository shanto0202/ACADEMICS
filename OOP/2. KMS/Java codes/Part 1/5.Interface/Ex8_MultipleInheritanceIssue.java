// Multiple Inheritance Issue

interface Alpha {

    default void reset() {
        System.out.println("Alpha's reset");
    }

}

interface Beta {

    default void reset() {
        System.out.println("Beta's reset");
    }

}

class TestClass implements Alpha, Beta {

    public void reset() {
        System.out.println("TestClass's reset");
    }

}

public class Ex8_MultipleInheritanceIssue {

    public static void main(String[] args) {

        TestClass t = new TestClass();
        t.reset();

    }
}

/*
Key Notes
---------
If two interfaces provide
same default method,
class must override it.
*/
