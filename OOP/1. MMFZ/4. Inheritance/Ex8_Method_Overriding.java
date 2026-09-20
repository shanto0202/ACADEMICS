
class Father {

    private String name;
    public int age;

    Father(String fName) {
        name = fName;
        age = 60;
    }

    public void show() {
        System.out.println("Father:" + name);
    }
}

class Son extends Father {

    private String name;
    public int age;

    Son(String sName, String fName) {
        super(fName);
        age = 20;
        name = sName;
    }

    public void show() {
        super.show(); // call base method
        System.out.println("Son:" + name);
    }

    public void showAge() {
        System.out.println("Son's Age: " + age);
    }
}

public class Ex8_Method_Overriding {

    public static void main(String[] args) {
        Father father = new Father("Rashid");
        Father son = new Son("Habib", "Jashim");
        father.show();
        son.show();
        ((Son) son).showAge(); // downcast
        System.out.println(son.age);
        System.out.println(((Son)son).age);
        father = son;
        father.show();
    }
}

/*
Key Notes:

1. Java methods are virtual by default for overriding.

2. Base reference can hold derived object.

3. Casting is needed to access Son-only methods.

4. Variable access depends on reference type, method call depends on object type.
 */
