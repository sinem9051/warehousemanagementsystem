#include "Shelf.h"

Shelf::Shelf(const string& category, int capacity)
    : category(category), capacity(capacity) {
}

const string& Shelf::getCategory() const {
    return category;
}

int Shelf::getCapacity() const {
    return capacity;
}

void Shelf::addProduct(const Product& product) {
    if (products.size() < static_cast<size_t>(capacity)) {
        products.push_back(product);
        cout << "Product added to shelf." << endl;
		
		writeToFile();
    } else {
        cout << "Shelf is full. Cannot add more products." << endl;
    }
}

void Shelf::writeToFile() const {
    
    ofstream file("shelf.txt", ios_base::app);
    file << "Category: " << category << "\n";
    file << "Product Name\tProduct Category\tProduct Price\tProduct Capacity\n";
    for (const auto& product : products) {
        file << product.getName() << '\t' << product.getCategory() << '\t'
             << product.getPrice() << '\t' << product.getCapacity() << '\n';
    }
    file << "--------------------------------\n";
    file.close();
}

