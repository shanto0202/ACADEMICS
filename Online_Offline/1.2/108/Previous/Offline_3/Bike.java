public class Bike extends Vehicle {
    private double EC;
    public Bike(String Rn, String On, double Bs, double Ec) throws ser_Exception {
        super(Rn, On, Bs);
        this.EC = Ec;
    }
    @Override
    public double ser_cost()
    {
        return bs + (EC * 2);
    }
    @Override
    public void service()
    {
        System.out.println("Servicing Bike: Tuning " + EC + "cc engine.");
    }
    @Override
    public void Details_dekhao()
    {
        super.Details_dekhao();
        System.out.println("Type: Bike | Capacity: " + EC + "cc");
    }
}