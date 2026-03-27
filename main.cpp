#include "inventory.h"
#include "auth.h"
#include <iostream>
#include "ui.h"
using namespace std;

int main() {
    authSystem auth;
    User* currentUser = nullptr;

    // Login Loop
    while (!currentUser) {
        currentUser = auth.login();
    }

    Inventory inv;
    int choice;

    // Role-based menu
    if (currentUser->getRole() == "admin") {
    while (true) {
        printTitle("Admin Menu");
        cout << "1. List Products\n";
        cout << "2. Add Product\n";
        cout << "3. Search Product\n";
        cout << "4. Update Product\n";
        cout << "5. Delete Product\n";
        cout << "6. Create Bill\n";
        cout << "7. Add User\n";
        cout << "8. List Users\n";
        cout << "9. Delete User\n";
        cout << "10. View Sales Report\n";
        cout << "11. View or Print saved bill\n";
        cout << "12. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) inv.listAll();
        else if (choice == 2) inv.addProduct();
        else if (choice == 3) inv.searchProduct();
        else if (choice == 4) inv.updateProduct();
        else if (choice == 5) inv.deleteProduct();
        else if (choice == 6) inv.createBill();
        else if (choice == 7) auth.addUser();
        else if (choice == 8) auth.listUser();
        else if (choice == 9) auth.delUser();
        else if (choice == 10) inv.viewSalesReport();
        else if (choice == 11) inv.printSavedBill();
        else if (choice == 12) break;
        else cout << "Invalid choice!\n";
    }
}
 
    else if (currentUser->getRole() == "cashier") {
        while (true) {
            printTitle("Cashier Menu");
            cout << "1. List Products\n";
            cout << "2. Create Bill\n";
            cout << "3. Print or Open saved bill\n";
            cout << "4. Exit\n";
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) inv.listAll();
            else if (choice == 2) inv.createBill();
            else if (choice == 3) inv.printSavedBill();
            else if (choice == 4) break;
            else cout << "Invalid choice!\n";
        }
    }

    return 0;
}
