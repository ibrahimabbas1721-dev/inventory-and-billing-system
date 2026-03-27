#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
class Product {
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    Product() {
        id = 0;
        price = 0.0;
        quantity = 0;
    }

    Product(int id, string name, double price, int quantity) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantity = quantity;
    }

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Setters
    void setQuantity(int q) { quantity = q; }

    void display() const {
        cout << "ID: " << id << "\n"
             << "Name: " << name << "\n"
             << "Price: " << price << "\n"
             << "Quantity: " << quantity << "\n";
    }
}; 


// --------------------------------------------------------------------> INVENTORY PART


class Inventory {
private:
    vector<Product> products;

public:
    Inventory() {
        loadFromFile();
    }

    void loadFromFile();   // read products.txt
    void saveToFile();     // write products.txt
    void listAll() const;  // display products
    void addProduct();  // add products in products.txt
    void searchProduct();
    void updateProduct();
    void deleteProduct();
    void createBill();

};
void Inventory::loadFromFile() {
    products.clear();  // in case function is called again

    ifstream file("data/products.txt");
    if (!file.is_open()) {
        return;
    }

    int id, quantity;
    double price;
    string name, temp;

    while (true) {
        if (!(file >> temp >> id)) break; // read "ID:" then number
        file.ignore(); // ignore space before getline

        getline(file, temp); // read "Name:"
        getline(file, name); // actual name

        file >> temp >> price;     // temp = "Price:" then double
        file >> temp >> quantity;  // temp = "Quantity:" then int

        getline(file, temp); // consume leftover newline
        getline(file, temp); // read "----"

        products.push_back(Product(id, name, price, quantity));
    }
    file.close();
}
void Inventory::listAll() const {
    if (products.empty()) {
        cout << "No products in inventory.\n";
        return;
    }

    for (const auto &p : products) {
        p.display();
        cout << "----\n";
    }
}
void Inventory::saveToFile() {
    ofstream file("data/products.txt");
    if (!file.is_open()) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (const auto &p : products) {
        file << "ID: " << p.getId() << "\n"
             << "Name:\n" << p.getName() << "\n"
             << "Price: " << p.getPrice() << "\n"
             << "Quantity: " << p.getQuantity() << "\n"
             << "----\n";
    }

    file.close();
}
void Inventory::addProduct() {
    int id, quantity;
    double price;
    string name;

    cout << "Enter Product ID: ";
    cin >> id;
    cin.ignore(); // clear newline for getline

    // CHECK IF PRODUCT EXISTS
    for (auto &p : products) {
        if (p.getId() == id) {
            cout << "Product with this ID already exists!\n";
            cout << "1. Create new product (cancel)\n";
            cout << "2. Update existing quantity\n";
            cout << "Choose option: ";
            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 2) {
                int addQty;
                cout << "Enter quantity to add: ";
                cin >> addQty;
                p.setQuantity(p.getQuantity() + addQty);
                cout << "Quantity updated successfully!\n";
                saveToFile();
            } else {
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
void Inventory::searchProduct() {
    if (products.empty()) {
        cout << "No products in inventory.\n";
        return;
    }

    cout << "Search by:\n1. ID\n2. Name\nChoice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        int id;
        cout << "Enter Product ID: ";
        cin >> id;

        for (const auto &p : products) {
            if (p.getId() == id) {
                cout << "\nProduct Found:\n";
                p.display();
                return;
            }
        }
        cout << "Product not found!\n";
    } 
    else if (choice == 2) {
        string name;
        cout << "Enter Product Name: ";
        getline(cin, name);

        for (const auto &p : products) {
            if (p.getName() == name) {
                cout << "\nProduct Found:\n";
                p.display();
                return;
            }
        }
        cout << "Product not found!\n";
    } 
    else {
        cout << "Invalid choice!\n";
    }
}
void Inventory::updateProduct() {
    if (products.empty()) {
        cout << "No products in inventory.\n";
        return;
    }

    int id;
    cout << "Enter Product ID to update: ";
    cin >> id;

    for (auto &p : products) {
        if (p.getId() == id) {
            cout << "\nCurrent Product Details:\n";
            p.display();

            cout << "\n1. Update Price\n2. Update Quantity\nChoice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                double newPrice;
                cout << "Enter new price: ";
                cin >> newPrice;
                p = Product(p.getId(), p.getName(), newPrice, p.getQuantity());
                cout << "Price updated!\n";
            } 
            else if (choice == 2) {
                int newQty;
                cout << "Enter new quantity: ";
                cin >> newQty;
                p.setQuantity(newQty);
                cout << "Quantity updated!\n";
            } 
            else {
                cout << "Invalid choice!\n";
            }

            saveToFile();
            return;
        }
    }

    cout << "Product not found!\n";
}
void Inventory::deleteProduct() {
    if (products.empty()) {
        cout << "No products in inventory.\n";
        return;
    }

    int id;
    cout << "Enter Product ID to delete: ";
    cin >> id;

    for (size_t i = 0; i < products.size(); ++i) {
        if (products[i].getId() == id) {
            cout << "Deleting product: " << products[i].getName() << "\n";
            products.erase(products.begin() + i);
            saveToFile();
            cout << "Product deleted successfully!\n";
            return;
        }
    }

    cout << "Product not found!\n";
}


// ----------------------------------------------------------------> Billing PART


void Inventory::createBill() {
    if (products.empty()) {
        cout << "No products available to sell.\n";
        return;
    }

    vector<pair<Product, int>> cart;  // product + quantity
    char choice;

    do {
        int id, qty;
        cout << "\nEnter Product ID to add to bill: ";
        cin >> id;

        bool found = false;
        for (auto &p : products) {
            if (p.getId() == id) {
                found = true;
                cout << "Enter quantity to buy: ";
                cin >> qty;

                if (qty > p.getQuantity()) {
                    cout << "Not enough stock! Only " << p.getQuantity() << " available.\n";
                } else {
                    cart.push_back({p, qty});
                    p.setQuantity(p.getQuantity() - qty);
                    cout << "Added to bill!\n";
                }
                break;
            }
        }

        if (!found) cout << "Product not found!\n";

        cout << "Add another item? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    // Save updated stock
    saveToFile();

    // Print Bill
    double total = 0;
    cout << "\n=== CUSTOMER BILL ===\n";
    cout << "--------------------------------------\n";
    cout << "ID\tName\tQty\tPrice\tTotal\n";
    cout << "--------------------------------------\n";

    for (auto &item : cart) {
        Product p = item.first;
        int q = item.second;
        double cost = p.getPrice() * q;
        total += cost;
        cout << p.getId() << "\t" << p.getName() << "\t" << q << "\t" << p.getPrice() << "\t" << cost << "\n";
    }

    cout << "--------------------------------------\n";
    cout << "Grand Total: " << total << endl;

    // Save bill to file
    ofstream billFile("bill.txt", ios::app);
    billFile << "=== BILL ===\n";
    for (auto &item : cart) {
        billFile << item.first.getName() << " x" << item.second << " = " 
                 << item.first.getPrice() * item.second << "\n";
    }
    billFile << "Total: " << total << "\n\n";
    billFile.close();

    cout << "\nBill saved to file successfully!\n";
}







int main() {
    Inventory inv;

    int choice;
    while (true) {
        cout << "\n=== INVENTORY MENU ===\n";
        cout << "1. List Products\n";
        cout << "2. Add Product\n";
        cout << "3. Search Product\n";
        cout << "4. Update Product\n";
        cout << "5. Delete Product\n";
        cout << "6. Create Bill\n";
        cout << "7. Exit\n";
        cout << "Choice: "; 
        cin >> choice;
        cin.ignore();

        if (choice == 1) inv.listAll();
        else if (choice == 2) inv.addProduct();
        else if (choice == 3) inv.searchProduct();
        else if (choice == 4) inv.updateProduct();
        else if (choice == 5) inv.deleteProduct();
        else if (choice == 6) inv.createBill();
        else if (choice == 7) break;
        else cout << "Invalid choice!\n";
    }

    return 0;
}
