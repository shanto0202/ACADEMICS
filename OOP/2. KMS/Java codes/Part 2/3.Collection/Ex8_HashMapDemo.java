// TF
import java.util.HashMap;
import java.util.Iterator;

public class Ex8_HashMapDemo {

    public static void main(String args[]) {

        HashMap<String, Double> balance = new HashMap<>();

        balance.put("John Doe", 3434.34);
        balance.put("Tom Smith", null);
        balance.put("Jane Baker", null);
        balance.put("Tod Hall", 99.22);
        balance.put(null, 0.0);

        Iterator<String> itr = balance.keySet().iterator();
        //Enumeration<String> itr1 = balance.keys();

        while (itr.hasNext()) { //hasMoreElements in Hashtable
            String key = itr.next();
            System.out.println(key + ": " + balance.get(key));
        }

        String key = "John Doe";
        double bal = balance.get(key);

        balance.put(key, bal + 1000);

        System.out.println(key + " new balance: " + balance.get(key));
    }
}

/*
Key Notes:

1. HashMap is NOT synchronized → faster.
2. Allows:
   - one null key
   - multiple null values
3. Uses hashing + chaining.
4. keySet() + iterator → traversal.
5. Preferred over Hashtable in modern Java.
*/
