#include "inventory.h"
#include <iostream>
#include <iomanip>
#include "ui.h"
#include <ctime>
#include <dirent.h>
#include <windows.h> // for ShellExecute
using namespace std;

// ---------- Product Definitions ----------
Product::Product(int id, string name, double price, int quantity)
    : id(id), name(name), price(price), quantity(quantity) {}

int Product::getId() const { return id; }
string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getQuantity() const { return quantity; }

void Product::setQuantity(int q) { quantity = q; }

void Product::display() const
{
    cout << left << setw(10) << id
         << setw(20) << name
         << setw(10) << price
         << setw(10) << quantity << endl;
}

// ---------- Inventory Definitions ----------
Inventory::Inventory() { loadFromFile(); }

void Inventory::saveToFile()
{
    ofstream file("data/inventory.txt");
    for (auto &p : products)
    {
        file << p.getId() << "," << p.getName() << "," << p.getPrice() << "," << p.getQuantity() << "\n";
    }
}

void Inventory::loadFromFile()
{
    ifstream file("data/inventory.txt");
    if (!file)
        return;

    products.clear();
    int id, qty;
    double price;
    string name;
    char comma;

    while (file >> id >> comma)
    {
        getline(file, name, ',');
        file >> price >> comma >> qty;
        file.ignore();
        products.push_back(Product(id, name, price, qty));
    }
}

void Inventory::listAll()
{

    if (products.empty())
    {
        cout << "No products in inventory.\n";
        return;
    }

    printTableHeader();

    for (auto &p : products)
        p.display();
}
void Inventory::addProduct()
{
    int id, quantity;
    double price;
    string name;

    printTitle("Add Product");

    cout << "Enter Product ID: ";
    cin >> id;
    cin.ignore(); // clear newline for getline

    // CHECK IF PRODUCT EXISTS
    for (auto &p : products)
    {
        if (p.getId() == id)
        {
            cout << "Product with this ID already exists!\n";
            cout << "1. Create new product (cancel)\n";
            cout << "2. Update existing quantity\n";
            cout << "Choose option: ";
            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 2)
            {
                int addQty;
                cout << "Enter quantity to add: ";
                cin >> addQty;
                p.setQuantity(p.getQuantity() + addQty);
                cout << "Quantity updated successfully!\n";
                saveToFile();
            }
            else
            {
                cout << "Cancelled! Product not added.\n";
            }
            return;
        }
    }

    // NEW PRODUCT CASE
    cout << "Enter Product Name: ";
    getline(cin, name);

    cout << "Enter Price: ";
    cin >> price;

    cout << "Enter Quantity: ";
    cin >> quantity;

    products.push_back(Product(id, name, price, quantity));
    saveToFile();

    cout << "Product added successfully!\n";
}
void Inventory::searchProduct()
{
    printTitle("Search Product");
    if (products.empty())
    {
        cout << "No products in inventory.\n";
        return;
    }

    cout << "Search by:\n1. ID\n2. Name\nChoice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        int id;
        cout << "Enter Product ID: ";
        cin >> id;

        for (const auto &p : products)
        {
            if (p.getId() == id)
            {
                cout << "\nProduct Found:\n";
                cout << left << setw(10) << "ID"
                     << setw(20) << "Name"
                     << setw(10) << "Price"
                     << setw(10) << "Qty" << endl;
                cout << "---------------------------------------------\n";
                p.display();
                return;
            }
        }
        cout << "Product not found!\n";
    }
    else if (choice == 2)
    {
        string name;
        cout << "Enter Product Name: ";
        getline(cin, name);

        for (const auto &p : products)
        {
            if (p.getName() == name)
            {
                cout << "\nProduct Found:\n";
                cout << left << setw(10) << "ID"
                     << setw(20) << "Name"
                     << setw(10) << "Price"
                     << setw(10) << "Qty" << endl;
                cout << "---------------------------------------------\n";
                p.display();
                return;
            }
        }
        cout << "Product not found!\n";
    }
    else
    {
        cout << "Invalid choice!\n";
    }
}
void Inventory::updateProduct()
{
    printTitle("Update Product");
    if (products.empty())
    {
        cout << "No products in inventory.\n";
        return;
    }

    int id;
    cout << "Enter Product ID to update: ";
    cin >> id;

    for (auto &p : products)
    {
        if (p.getId() == id)
        {
            cout << "\nCurrent Product Details:\n";
            cout << left << setw(10) << "ID"
                 << setw(20) << "Name"
                 << setw(10) << "Price"
                 << setw(10) << "Qty" << endl;
            cout << "---------------------------------------------\n";
            p.display();

            cout << "\n1. Update Price\n2. Update Quantity\nChoice: ";
            int choice;
            cin >> choice;

            if (choice == 1)
            {
                double newPrice;
                cout << "Enter new price: ";
                cin >> newPrice;
                p = Product(p.getId(), p.getName(), newPrice, p.getQuantity());
                cout << "Price updated!\n";
            }
            else if (choice == 2)
            {
                int newQty;
                cout << "Enter new quantity: ";
                cin >> newQty;
                p.setQuantity(newQty);
                cout << "Quantity updated!\n";
            }
            else
            {
                cout << "Invalid choice!\n";
            }

            saveToFile();
            return;
        }
    }

    cout << "Product not found!\n";
}
void Inventory::deleteProduct()
{
    printTitle("Delete Product");
    if (products.empty())
    {
        cout << "No products in inventory.\n";
        return;
    }

    int id;
    cout << "Enter Product ID to delete: ";
    cin >> id;

    for (size_t i = 0; i < products.size(); ++i)
    {
        if (products[i].getId() == id)
        {
            cout << "Deleting product: " << products[i].getName() << "\n";
            products.erase(products.begin() + i);
            saveToFile();
            cout << "Product deleted successfully!\n";
            return;
        }
    }

    cout << "Product not found!\n";
}

void Inventory::createBill()
{
    printTitle("Create Bill");
    if (products.empty())
    {
        cout << "No products available to sell.\n";
        return;
    }

    vector<pair<Product, int>> cart; // product + quantity
    char choice;

    do
    {
        string searchInput;
        int qty;

        cout << "\nEnter Product ID or Name to add to bill: ";
        cin >> ws; // clear any leftover whitespace
        getline(cin, searchInput);

        bool found = false;
        for (auto &p : products)
        {
            // Match by ID or Name
            if (to_string(p.getId()) == searchInput || p.getName() == searchInput)
            {
                found = true;
                cout << "Enter quantity to buy: ";
                cin >> qty;

                if (qty > p.getQuantity())
                {
                    cout << "Not enough stock! Only " << p.getQuantity() << " available.\n";
                }
                else
                {
                    cart.push_back({p, qty});
                    p.setQuantity(p.getQuantity() - qty);
                    cout << "Added to bill!\n";
                }
                break;
            }
        }

        if (!found)
            cout << "Product not found!\n";

        cout << "Add another item? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    // Save updated stock
    saveToFile();

    // Print Bill
    double total = 0;
    printTitle("Customer Bill");
    cout << "--------------------------------------\n";
    cout << "ID\tName\tQty\tPrice\tTotal\n";
    cout << "--------------------------------------\n";

    for (auto &item : cart)
    {
        Product p = item.first;
        int q = item.second;
        double cost = p.getPrice() * q;
        total += cost;
        cout << p.getId() << "\t" << p.getName() << "\t" << q << "\t"
             << p.getPrice() << "\t" << cost << "\n";
    }

    cout << "--------------------------------------\n";
    cout << "Grand Total: " << total << endl;

    // ================================
    // 📁 Save each bill separately
    // ================================

    // Create "bills" folder if it doesn't exist
    system("mkdir bills >nul 2>nul");

    // Create unique filename using date/time
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string filename = "bills/bill_";
    filename += to_string(1900 + ltm->tm_year) + "_";
    filename += to_string(1 + ltm->tm_mon) + "_";
    filename += to_string(ltm->tm_mday) + "_";
    filename += to_string(ltm->tm_hour) + to_string(ltm->tm_min) + ".txt";

    ofstream billFile(filename);
    if (!billFile)
    {
        cout << "Error creating bill file!\n";
        return;
    }

    billFile << "=== CUSTOMER BILL ===\n";
    billFile << "--------------------------------------\n";
    billFile << "ID\tName\tQty\tPrice\tTotal\n";
    billFile << "--------------------------------------\n";

    for (auto &item : cart)
    {
        double cost = item.first.getPrice() * item.second;
        billFile << item.first.getId() << "\t" << item.first.getName()
                 << "\t" << item.second << "\t" << item.first.getPrice()
                 << "\t" << cost << "\n";
    }

    billFile << "--------------------------------------\n";
    billFile << "Grand Total: " << total << "\n";
    billFile.close();

    cout << "\nBill saved as: " << filename << endl;

    // ================================
    // 🧾 Log total sale in sales_report.txt
    // ================================
    ofstream salesFile("sales_reports/sales_report.txt", ios::app);
    if (salesFile)
    {
        salesFile << total << "\n";
        salesFile.close();
    }

    cout << "Sale recorded successfully!\n";
}
void Inventory::viewSalesReport()
{
    ifstream file("sales_report.txt");
    if (!file)
    {
        cout << "No sales data found.\n";
        return;
    }

    double totalSale = 0, sale;
    int count = 0;
    while (file >> sale)
    {
        totalSale += sale;
        count++;
    }

    printTitle("SALES REPORT");
    cout << "Total Bills: " << count << endl;
    cout << "Total Revenue: " << totalSale << endl;
}

void Inventory::printSavedBill()
{
    string folderPath = "bills";
    DIR *dir = opendir(folderPath.c_str());
    if (!dir)
    {
        cout << "No bills directory found.\n";
        return;
    }

    vector<string> billFiles;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        string name = entry->d_name;
        if (name.find(".txt") != string::npos)
        {
            billFiles.push_back(folderPath + "/" + name);
        }
    }
    closedir(dir);

    if (billFiles.empty())
    {
        cout << "No bills found!\n";
        return;
    }

    for (size_t i = 0; i < billFiles.size(); ++i)
    {
        cout << i + 1 << ". " << billFiles[i] << endl;
    }

    int choice;
    cout << "Enter bill number to open: ";
    cin >> choice;

    if (choice < 1 || choice > billFiles.size())
    {
        cout << "Invalid choice.\n";
        return;
    }

    string selectedFile = billFiles[choice - 1];
    ifstream billFile(selectedFile);
    if (!billFile)
    {
        cout << "Error opening bill file.\n";
        return;
    }

    printTitle("Bill Preview");
    string line;
    while (getline(billFile, line))
    {
        cout << line << endl;
    }
    billFile.close();

    char printChoice;
    cout << "\nDo you want to print this bill? (y/n): ";
    cin >> printChoice;

    if (printChoice == 'y' || printChoice == 'Y')
    {
        HINSTANCE result = ShellExecuteA(
            NULL,
            "print",
            selectedFile.c_str(),
            NULL,
            NULL,
            SW_HIDE);

        if ((int)result <= 32)
            cout << "❌ Failed to send bill to printer.\n";
        else
            cout << "🖨️ Bill sent to printer successfully!\n";
    }
}
