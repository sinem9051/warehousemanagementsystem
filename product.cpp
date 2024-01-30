#include "Product.h"
#include <iostream>

Product::Product(const string& name, const string& category, double price, int capacity)
    : name(name), category(category), price(price), capacity(capacity) {}

const string& Product::getName() const {
    return name;
}

const string& Product::getCategory() const {
    return category;
}

double Product::getPrice() const {
    return price;
}

int Product::getCapacity() const {
    return capacity;
}

void Product::setPrice(double price) {
    this->price = price;
}

void Product::setCapacity(int capacity) {
    this->capacity = capacity;
}

void Product::displayProduct() const {
    cout << "Name: " << name << ", Category: " << category << ", Price: " << price << ", Capacity: " << capacity << endl;
}

int Product::getOrderedQuantity() const {
    return orderedQuantity;
}


