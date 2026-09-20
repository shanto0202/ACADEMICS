public abstract class Vehicle implements Serviceable {
    protected String rn;
    protected String on;
    protected double bs;
    public Vehicle(String Rn, String On, double Bs) throws ser_Exception {
        if (Rn == null || Rn.trim().isEmpty())
        {
            throw new ser_Exception("Registration number cannot be empty.");
        }
        if (Bs < 0) 
        {
            throw new ser_Exception("Base service cost cannot be negative.");
        }
        this.rn = Rn;
        this.on = On;
        this.bs = Bs;
    }
    public abstract double ser_cost();
    public void Details_dekhao()
    {
        System.out.println("Registration: " + rn);
        System.out.println("Owner: " + on);
        System.out.println("Base Cost: " + bs);
    }
    @Override
    public double mot_cost()
    {
        return ser_cost();
    }
}