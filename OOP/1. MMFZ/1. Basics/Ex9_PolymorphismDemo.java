// Demonstrates polymorphism using constructor overloading

import java.time.LocalDate;

class MyDate {

    // Encapsulated data members
    private int day;
    private int month;
    private int year;

    // Constructor 1: takes date as String (YYYY-MM-DD)
    MyDate(String str) {
        LocalDate date = LocalDate.parse(str);
        day = date.getDayOfMonth();
        month = date.getMonthValue();
        year = date.getYear();
    }

    // Constructor 2: takes separate day, month, year
    MyDate(int newDay, int newMonth, int newYear) {
        day = newDay;
        month = newMonth;
        year = newYear;
    }

    // Method to display the date
    public void showMyDate() {
        System.out.println(day + "/" + month + "/" + year);
    }
}

public class Ex9_PolymorphismDemo {

    public static void main(String[] args) {

        // Two objects using different constructors (constructor overloading)
        MyDate sDate = new MyDate("2024-05-12");
        MyDate iDate = new MyDate(23, 7, 2025);

        // Display dates
        sDate.showMyDate();
        iDate.showMyDate();
    }
}

/*
Key Notes:
1. Polymorphism → one interface, multiple implementations.
2. Here achieved using constructor overloading.
3. Same class, different constructor parameter types.
4. Java supports function/constructor overloading.
5. Java does NOT support operator overloading (unlike C++).
*/
