#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Product.h"
#include "Manager.h"  

class Employee {


public:
	
    Employee(const Manager& manager);

    void createOrder();
    void viewOrders() const;
    void prepareOrder();
    void writeOrdersToFile() const;
    void readOrdersFromFile();
    int getProductCapacity(const string& productName) const;
	 Product findProduct(const string& name) const;
	
	

private:
	Manager manager;  
    vector<Product> orders;

    void displayProduct(const Product& product)const;
    void writeEmployeeDataToFile() const;
    void readEmployeeDataFromFile();
    
    
};

#endif

