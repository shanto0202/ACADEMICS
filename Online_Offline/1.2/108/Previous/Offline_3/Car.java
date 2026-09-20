public class Car extends Vehicle {
    private int ND;
    public Car(String Rn, String On, double Bs, int Nd) throws ser_Exception
    {
        super(Rn, On, Bs);
        this.ND = Nd;
    }
    @Override
    public double ser_cost()
    {
        return bs + (ND * 500);
    }
    @Override
    public void service()
    {
        System.out.println("Servicing Car: Checking " + ND + " doors and engine.");
    }
    @Override
    public void Details_dekhao()
    {
        super.Details_dekhao();
        System.out.println("Type: Car | Doors: " + ND);
    }
}