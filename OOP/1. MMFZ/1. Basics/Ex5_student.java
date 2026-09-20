import java.util.Scanner;

class Student {
    private String name;
    private int rollno;
    private double cgpa;

    // setter -getter
    public void setName(String N) {
        name = N;
    }

    public String getName() {
        return name;
    }

    public void setRollno(int R) {
        rollno = R;
    }

    public int getRollno() {
        return rollno;
    };

    public void setCGPA(double CGPA) {
        cgpa = CGPA;
    }

    public double getCGPA() {
        return cgpa;
    }
}

public class Ex5_student {
    public static void main(String[] args) {
        Student std = new Student();
        String iname = new String();
        Scanner obj = new Scanner(System.in);
        int irollno;
        double icgpa;
        System.out.print("Enter name: ");
        iname = obj.nextLine();
        std.setName(iname);
        System.out.print("Enter Rollno: ");
        irollno = obj.nextInt();
        std.setRollno(irollno);
        System.out.print("Enter CGPA: ");
        icgpa = obj.nextDouble();
        std.setCGPA(icgpa);
        System.out.print("Name:" + std.getName() + "Rollno: " + std.getRollno() + "CGPA:" + std.getCGPA());
        obj.close();
    }
}