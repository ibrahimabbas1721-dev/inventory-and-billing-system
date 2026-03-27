#ifndef INVENTORY_H
#define INVENTORY_H

#include "product.h"
#include <vector>
#include <fstream>

class Inventory {
private:
    vector<Product> products;
    void saveToFile();
    void loadFromFile();

public:
    Inventory();

    void listAll();
    void addProduct();
    void searchProduct();
    void updateProduct();
    void deleteProduct();
    void createBill();
    void viewSalesReport();
    void printSavedBill();
};

#endif
