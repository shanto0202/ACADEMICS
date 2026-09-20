import java.util.ArrayList;
import java.util.List;
public class WorkshopManager {
    private List<Vehicle> v1 = new ArrayList<>();
    private static final double ms = 50000.0; 
    public void Add_veh(Vehicle v) throws ser_Exception
    {
        if (v.ser_cost() > ms)
        {
            throw new ser_Exception("Service cost (" + v.ser_cost() + ") exceeds maximum limit.");
        }
        v1.add(v);
        System.out.println("Vehicle added successfully: " + v.rn);
    }
    public void sob_dekhao()
    {
        System.out.println("\n--- Workshop Inventory ---");
        for (Vehicle v : v1)
        {
            v.Details_dekhao();
            System.out.println("Total Service Cost: " + v.mot_cost());
            v.service();
            System.out.println("--------------------------");
        }
    }
    public double mot_lav()
    {
        double t = 0;
        for (Vehicle v : v1)
        {
            t += v.mot_cost();
        }
        return t;
    }
}