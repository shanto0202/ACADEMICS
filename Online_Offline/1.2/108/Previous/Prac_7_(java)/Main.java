
import java.util.Random;

public class Main {

    public static void main(String[] args) {
        Account a[] = new Account[6];
        Random r = new Random();
        for (int i = 0; i < 6; i++) {
            a[i] = new Account(i + 1, "ACC" + (i + 1), 10000 * r.nextDouble());
        }
        Branch b[] = new Branch[2];
        for (int i = 0; i < 2; i++) {
            b[i] = new Branch(i + 1, "BR" + (i + 1));
        }
        b[0].addAccount(a[0]);
        b[0].addAccount(a[1]);
        b[1].addAccount(a[2]);
        b[1].addAccount(a[3]);
        b[1].addAccount(a[4]);
        b[1].addAccount(a[5]);

        System.out.println(b[0].getBranchBalance());
        System.out.println(b[1].getBranchBalance());
        System.out.println(b[0].getMinBalanceAccount().getCustomer());
        System.out.println(b[1].getMinBalanceAccount().getCustomer());

        Branch.transferBalance(a[4], a[3], 100);
        Branch.printAllBranchesInfo();
    }
}
