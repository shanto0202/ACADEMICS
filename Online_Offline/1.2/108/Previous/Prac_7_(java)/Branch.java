
public class Branch {

    private int id;
    private String name;
    private Account[] accounts;
    private int accountCount;

    // Static → belongs to class, shared by all objects
    private static Branch[] branches = new Branch[20];
    private static int branchCount = 0;

    public Branch(int id, String name) {
        this.id = id;
        this.name = name;
        accounts = new Account[10];
        accountCount = 0;

        // store every branch object
        branches[branchCount++] = this;
    }

    // Add account to this branch
    public void addAccount(Account a) {
        accounts[accountCount++] = a;
    }

    // Total balance of this branch
    public double getBranchBalance() {
        double total = 0;
        for (int i = 0; i < accountCount; i++) {
            total += accounts[i].getBalance();
        }
        return total;
    }

    // Minimum balance account of this branch
    public Account getMinBalanceAccount() {
        Account min = accounts[0];
        for (int i = 1; i < accountCount; i++) {
            if (accounts[i].getBalance() < min.getBalance()) {
                min = accounts[i];
            }
        }
        return min;
    }

    // Transfer between two accounts
    public static void transferBalance(Account from, Account to, double amount) {
        if (from.withdraw(amount)) {
            to.deposit(amount);
        }
    }

    // Print all branches and accounts
    public static void printAllBranchesInfo() {
        for (int i = 0; i < branchCount; i++) {
            Branch b = branches[i];
            System.out.println("Branch ID: " + b.id + ", Name: " + b.name);

            for (int j = 0; j < b.accountCount; j++) {
                Account a = b.accounts[j];
                System.out.println(
                        "  Account No: " + a.getNumber()
                        + ", Customer: " + a.getCustomer()
                        + ", Balance: " + a.getBalance()
                );
            }
        }
    }
}
