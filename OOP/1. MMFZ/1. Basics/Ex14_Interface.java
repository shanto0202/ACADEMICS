// Interface definition

interface Fly {

    // method declaration only
    public String fly();
}

// Dog class implementing Ex14_Fly
class Dog implements Fly {

    public String fly() {
        return "I cannot fly.";
    }

    public String MakeSound() {
        return "I sound berk.";
    }
}

// Bird class implementing Ex14_Ex14_Fly
class Bird implements Fly {

    public String fly() {
        return "I fly in the sky.";
    }

    public String MakeSound() {
        return "I sound chi-chi.";
    }
}

// Biman class implementing Ex14_Fly
class Biman implements Fly {

    public String fly() {
        return "I fly too high in the sky.";
    }
}

// Main class to demonstrate interface use
public class Ex14_Interface {

    public static void main(String[] args) {

        Fly doggy = new Dog();
        Bird sweety = new Bird();
        Fly gogon = new Biman();

        System.out.println("I am a dog." + doggy.fly() + ((Dog) doggy).MakeSound());
        System.out.println("I am a bird." + sweety.fly() + sweety.MakeSound());
        System.out.println("I am a Biman." + gogon.fly());
    }
}

/*
Key Notes:
1. Interface → contains only method declarations.
2. Classes implement interface using "implements".
3. Interface enables abstraction and polymorphism.
4. Multiple classes can implement the same interface.
 */