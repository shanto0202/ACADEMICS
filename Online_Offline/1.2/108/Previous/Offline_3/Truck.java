public class Truck extends Vehicle {
    private double l;
    public Truck(String r, String o, double bs, double lc) throws ser_Exception {
        super(r, o, bs);
        this.l = lc;
    }
    @Override
    public double ser_cost() 
    {
        return bs + (l * 1000);
    }
    @Override
    public void service()
    {
        System.out.println("Servicing Truck: Checking hydraulics for " + l + " ton load.");
    }
    @Override
    public void Details_dekhao()
    {
        super.Details_dekhao();
        System.out.println("Type: Truck | Load: " + l + " tons");
    }
}