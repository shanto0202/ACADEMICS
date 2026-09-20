
enum HttpStatus {

    OK(200, "OK"),
    NOT_FOUND(404, "Not Found"),
    INTERNAL_ERROR(500, "Internal Server Error");

    private int code;
    private String message;

    // Constructor
    HttpStatus(int code, String message) {
        this.code = code;
        this.message = message;
    }

    // isError()
    public boolean isError() {
        return this != OK;
    }

    // toString()
    @Override
    public String toString() {
        return code + " " + message;
    }

    // fromCode()
    public static HttpStatus fromCode(int code) {
        for (HttpStatus status : HttpStatus.values()) {
            if (status.code == code) {
                return status;
            }
        }
        return null;
    }
}

// Test class
public class Ex9 {

    public static void main(String[] args) {

        System.out.println(HttpStatus.OK);                 // 200 OK
        System.out.println(HttpStatus.NOT_FOUND);          // 404 Not Found
        System.out.println(HttpStatus.INTERNAL_ERROR);     // 500 Internal Server Error

        System.out.println(HttpStatus.OK.isError());       // false
        System.out.println(HttpStatus.NOT_FOUND.isError()); // true

        System.out.println(HttpStatus.fromCode(200));      // OK
        System.out.println(HttpStatus.fromCode(404));      // NOT_FOUND
        System.out.println(HttpStatus.fromCode(999));      // null
    }
}

/*
Key Notes:

1. Enum can have:
   - fields
   - constructor
   - methods

2. Each constant:
   OK(200, "OK") → calls constructor

3. isError():
   - returns false for OK
   - true for others

4. toString():
   - overridden to print "code message"

5. fromCode():
   - static method
   - loops through values()
   - returns matching enum or null

6. values():
   - returns all enum constants

7. Very important:
   - enum constructor is implicitly private

8. Output format:
   - matches exactly question requirement
*/
