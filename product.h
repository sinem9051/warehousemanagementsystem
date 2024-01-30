#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product {
private:
    string name;
    string category;
    double price;
    int capacity;
 	int orderedQuantity; 
public:
    Product(const string& name, const string& category, double price, int capacity);
    
    
    const string& getName() const;
    const string& getCategory() const;
    double getPrice() const;
    int getCapacity() const;
    
    void setPrice(double price);
    void setCapacity(int capacity);
    
    void displayProduct() const;
	int getOrderedQuantity() const;
	
	
};

#endif

