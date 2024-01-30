#ifndef SHELF_H
#define SHELF_H

#include "Product.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Shelf {
private:
    string category;
    int capacity;
    vector<Product> products;

public:
    
	Shelf(const string& category, int capacity);
    
	const string& getCategory() const;
    int getCapacity() const;
    void addProduct(const Product& product);
	void writeToFile() const;
};

#endif

