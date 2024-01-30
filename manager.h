#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include "Product.h"

class Manager {
private:
    vector<Product> products;

public:
    void addProduct();
    void viewProducts() const;
    void removeProduct();
    void modifyProduct();
    void shelveManagement();
    void writeToFile() const;
    void readFromFile();
    Product findProduct(const string& name) const;
	void removeProductCapacity(const string& productName, int quantity);
  	void updateProductFile() const;
  	void updateFileWithProduct(const Product& updatedProduct);
    int getProductCapacity(const string& productName) const;
    void updateShelfFile(const Product& product);

private:
    void displayProduct(const Product& product) const;
    
    void readShelfFile() const;  
    void displayShelf() const;   
    
};

#endif

