#include <bits/stdc++.h>
using namespace std;
#define ll long long

class Product
{
private:
    string productName;
    string productID;
    double price;
    int stockChanges[100];
    int numStockChanges;

public:
    Product()
    {
        productName = "";
        productID = "";
        price = 0;
        numStockChanges = 0;
    }
    Product(string ProductName, string ProductID, double Price)
    {
        productName = ProductName;
        productID = ProductID;
        price = Price;
        numStockChanges = 0;
    }
    void addStock(int amount)
    {
        if (numStockChanges > 0)
        {
            stockChanges[numStockChanges] = stockChanges[numStockChanges - 1] + amount;
        }
        else
        {
            stockChanges[numStockChanges] = amount;
        }
        numStockChanges++;
    }
    // void reduceStock(int amount)
    // {
    //     return;
    // }
    string getProductID()
    {
        return productID;
    }
    string getProductName()
    {
        return productName;
    }
    double getProductPrice()
    {
        return price;
    }
    int getProductStock()
    {
        if (numStockChanges == 0)
            return 0;
        return stockChanges[numStockChanges - 1];
    }
    void display()
    {
        cout << "Product: " << productName << "(ID: " << productID << "), Price: Tk." << price << ", Stock: " << stockChanges[numStockChanges - 1] << endl;
    }
};

class Inventory
{
private:
    Product *products;
    int numProducts;
    int maxProducts;
    int amount;

public:
    Inventory()
    {
        numProducts = 0;
        maxProducts = 0;
        amount = 0;
    }
    Inventory(int MaxProducts)
    {
        maxProducts = MaxProducts;
        numProducts = 0;
        products = new Product[maxProducts];
    }
    Inventory(Product *products, int numProducts, int maxProducts)
    {
    }
    // Copy constructor
    Inventory(const Inventory &prev)
    {
        maxProducts = prev.maxProducts;
        numProducts = prev.numProducts;
        products = new Product[maxProducts];
        for (int i = 0; i < numProducts; i++)
        {
            products[i] = prev.products[i];
        }
    }
    ~Inventory()
    {
        delete[] products;
    }
    void addProduct(Product p)
    {
        if (numProducts == maxProducts)
        {
            cout << "Inventory full. Cannot add any more product" << endl;
            return;
        }
        products[numProducts] = p;
        cout << "Product added with ID: " << products[numProducts].getProductID() << endl;
        numProducts++;
    }
    void updateProductStock(string ProductID, int Amount)
    {
        for (int i = 0; i < numProducts; i++)
        {
            if (products[i].getProductID() == ProductID)
            {
                products[i].addStock(Amount);
            }
        }
    }
    void listAllProducts()
    {
        for (int i = 0; i < numProducts; i++)
        {
            cout << "Product: " << products[i].getProductName() << "(ID: " << products[i].getProductID() << "), Price: Tk." << products[i].getProductPrice() << ", Stock: " << products[i].getProductStock() << endl;
        }
    }
    Product getMostStockedProduct()
    {
        int m = INT_MIN;
        for (int i = 0; i < numProducts; i++)
        {
            if (m < products[i].getProductStock())
            {
                m = products[i].getProductStock();
            }
        }
        for (int i = 0; i < numProducts; i++)
        {
            if (m == products[i].getProductStock())
            {
                return products[i];
            }
        }
        return Product();
    }
};

int main()
{
    Inventory inv1(5);
    Product p1("Laptop", "P001", 50000);
    Product p2("Smartphone", "P002", 30000);
    Product p3("Tablet", "P003", 25000);
    Product p4("Smartwatch", "P004", 4000);
    Product p5("Headphones", "P005", 2000);
    Product p6("Charger", "P006", 1000);
    inv1.addProduct(p1);
    inv1.addProduct(p2);
    inv1.addProduct(p3);
    inv1.addProduct(p4);
    inv1.addProduct(p5);
    inv1.addProduct(p6);
    inv1.updateProductStock("P001", 50);
    inv1.updateProductStock("P001", -10);
    inv1.updateProductStock("P003", 70);
    inv1.updateProductStock("P002", 70);
    inv1.updateProductStock("P002", -5);
    inv1.updateProductStock("P003", -10);
    cout << "\nProducts in Inventory 1:\n";
    inv1.listAllProducts();
    cout << "\nMost Stocked Product in Inventory 1:\n";
    inv1.getMostStockedProduct().display();
    Inventory inv2 = inv1;
    inv2.updateProductStock("P003", 10);
    inv2.updateProductStock("P002", 10);
    inv2.updateProductStock("P002", -5);
    cout << "\nProducts in Inventory 2:\n";
    inv2.listAllProducts();
    cout << "\nMost Stocked Product in Inventory 1:\n";
    inv1.getMostStockedProduct().display();
    cout << "\nMost Stocked Product in Inventory 2:\n";
    inv2.getMostStockedProduct().display();
    return 0;
}
