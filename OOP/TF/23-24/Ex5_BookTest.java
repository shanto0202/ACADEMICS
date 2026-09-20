
import java.util.HashSet;
import java.util.Objects;

// Custom class
class Book {

    private String title;
    private String author;
    private int year;
    private int edition;

    // Constructor
    Book(String title, String author, int year, int edition) {
        this.title = title;
        this.author = author;
        this.year = year;
        this.edition = edition;
    }

    // Override toString() for printing
    @Override
    public String toString() {
        return "Book (" + title + ", " + author + ", " + year + ", " + edition + ")";
    }

    // Override equals() (ignore edition)
    //@Override
    public boolean equals(Object o) {

        // Same reference → true
        if (o == this) {
            return true;
        }

        // If not same class → false
        if (!(o instanceof Book)) {
            return false;
        }

        // Typecast
        Book b = (Book) o;

        // Compare content (ignore edition)
        return this.year == b.year
                && Objects.equals(this.title, b.title)
                && Objects.equals(this.author, b.author);
    }

    // Override hashCode() to match equals()
    @Override
    public int hashCode() {
        return Objects.hash(title, author, year);
    }
}

public class Ex5_BookTest {

    public static void main(String[] args) {

        Book b1 = new Book("1984", "George Orwell", 1949, 1);
        Book b2 = new Book("1984", "George Orwell", 1949, 2);

        // toString() used automatically
        System.out.println(b1);              // Book (1984, George Orwell, 1949, 1)

        // == checks reference
        System.out.println(b1 == b2);        // false

        // equals() checks content
        System.out.println(b1.equals(b2));   // true

        // HashSet usage
        HashSet<Book> set = new HashSet<>();

        set.add(b1);
        set.add(b2);

        // Only one stored (duplicate removed)
        System.out.println(set.size());      // 1
    }
}

/*
Key Notes:

1. toString():
   - Used when printing object directly
   - Formats output as required

2. == vs equals():

   - == → compares reference (memory address)
   - equals() → compares content (if overridden)

3. In this problem:
   - edition is ignored in equals()
   - so b1 and b2 are considered SAME

4. equals() logic:
   - compare title, author, year
   - ignore edition

5. hashCode():
   - must match equals()
   - uses same fields (title, author, year)

6. HashSet behavior:
   - stores unique elements
   - uses hashCode() first
   - then equals() to confirm

7. Why set size = 1?
   - b1 and b2 are equal
   - same hashCode
   - so duplicate removed

8. Very important rule:
   - If equals() is overridden → hashCode() MUST be overridden

9. Common mistake:
   - including edition in hashCode but not in equals → WRONG

10. Final understanding:
   - Logical equality ≠ reference equality
*/
