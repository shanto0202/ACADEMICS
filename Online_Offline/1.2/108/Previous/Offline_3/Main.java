public class Main {
    public static void main(String[] args) {
        WorkshopManager m = new WorkshopManager();
        System.out.println("=== Vehicle Management System ===");
        try {
            Vehicle c = new Car("C-1001", "ABS", 5000, 4);
            Vehicle b = new Bike("B-2002", "RKS", 2000, 150);
            Vehicle t = new Truck("T-3003", "SBM", 10000, 5);
            m.Add_veh(c);
            m.Add_veh(b);
            m.Add_veh(t);
            m.sob_dekhao();
            System.out.println("Total Revenue: " + m.mot_lav() + " BDT");
            System.out.println("\n--- Testing ---");
            try {
                System.out.print("1. Empty Reg: ");
                new Car("", "TestUser", 5000, 4);
            } catch (ser_Exception ops) {
                System.out.println( ops.getMessage());
            }
            try {
                System.out.print("2. Negative Cost: ");
                new Bike("B-ERR", "TestUser", -100, 100);
            } catch (ser_Exception ops) {
                System.out.println( ops.getMessage());
            }
            try {
                System.out.print("3. Cost Limit: ");
                Vehicle hugeTruck = new Truck("T-HUGE", "RichUser", 10000, 50);
                m.Add_veh(hugeTruck);
            } catch (ser_Exception ops) {
                System.out.println( ops.getMessage());
            }
        } catch (ser_Exception ops) {
            System.out.println("General Error: " + ops.getMessage());
        }
    }
}
