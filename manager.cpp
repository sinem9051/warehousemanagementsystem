#include "Manager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream> 

using namespace std;

const std::string FILENAME = "products.txt";   
const std::string SHELF_FILE = "shelf.txt";    


void Manager::addProduct() {
    string name, category;
    double price;
    int capacity;

    cout << "Enter product name: ";
    cin >> name;
    cout << "Enter product category: ";
    cin >> category;
    cout << "Enter product price: ";
    cin >> price;
    cout << "Enter product capacity: ";
    cin >> capacity;

   
    auto it = find_if(products.begin(), products.end(),
                      [name, category, price](const Product& p) {
                          return p.getName() == name && p.getCategory() == category && p.getPrice() == price;
                      });

    if (it != products.end()) {
        it->setCapacity(it->getCapacity() + capacity);
        cout << "Product updated successfully!" << endl;
        writeToFile();
        shelveManagement(); 
        
        
    } else {
        
        Product newProduct(name, category, price, capacity);
        products.push_back(newProduct);

       
        writeToFile();

    
    updateShelfFile(newProduct);
    shelveManagement(); 

    std::cout << "Product added successfully!" << std::endl;
}
}

Product Manager::findProduct(const std::string& name) const {
    for (const auto& product : products) {
        if (product.getName() == name) {
            return product;
        }
    }
    
    return Product("Not Found", "", 0.0, 0);
}

void Manager::viewProducts() const {
    if (products.empty()) {
        cout << "No products available." << endl;
        return;
    }

    cout << "Product List:" << endl;
    for (const auto& product : products) {
        displayProduct(product);
    }
}

void Manager::removeProduct() {
    if (products.empty()) {
        cout << "No products available to remove." << endl;
        return;
    }

    string name;
    cout << "Enter the name of the product to remove: ";
    cin >> name;

    auto it = remove_if(products.begin(), products.end(),
                        [name](const Product& product) { return product.getName() == name; });

    if (it != products.end()) {
        products.erase(it, products.end());
        
       
        writeToFile();

        cout << "Product removed successfully!" << endl;
    } else {
        cout << "Product not found." << endl;
    }
    shelveManagement(); 
 

}

void Manager::modifyProduct() {
    if (products.empty()) {
        cout << "No products available to modify." << endl;
        return;
    }

    string name;
    cout << "Enter the name of the product to modify: ";
    cin >> name;

    for (auto& product : products) {
        if (product.getName() == name) {
            double newPrice;
            int newCapacity;

            cout << "Enter the new price: ";
            cin >> newPrice;
            cout << "Enter the new capacity: ";
            cin >> newCapacity;

            product.setPrice(newPrice);
            product.setCapacity(newCapacity);

            
            writeToFile();

            cout << "Product modified successfully!" << endl;
            
            return;
        }
        
        writeToFile();
        
    }
    

    cout << "Product not found." << endl;
}

void Manager::shelveManagement() {
    if (products.empty()) {
        cout << "No products available for shelve management." << endl;
        return;
    }

    products.clear();
    readFromFile();

   
    ofstream shelfFile(SHELF_FILE, ios::trunc); 

    if (!shelfFile.is_open()) {
        cerr << "Unable to open shelf data file for updating." << endl;
        return;
    }

    string currentCategory;  

    for (const auto &product : products) {
        
        if (currentCategory != product.getCategory()) {
            shelfFile << product.getCategory() << "\n";
            shelfFile << "--------------\n";
            currentCategory = product.getCategory();
        }

        
        shelfFile << product.getName() << ", " << product.getCapacity() << "\n\n";
    }

   
    shelfFile.close();

    
    if (shelfFile.fail()) {
        cerr << "Error updating shelf data file." << endl;
        perror("Error");
    }
    
    
    cout << "Shelve management..." << endl;
}

void Manager::displayProduct(const Product& product) const {
    
    cout << "Name: " << product.getName() << ", Category: " << product.getCategory()
              << ", Price: " << product.getPrice() << ", Capacity: " << product.getCapacity() << endl;
}

void Manager::readFromFile() {
    ifstream file(FILENAME);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, category;
            double price;
            int capacity;

            getline(ss, name, ',');
            getline(ss, category, ',');
            ss >> price;
            ss.ignore();  
            ss >> capacity;

            Product newProduct(name, category, price, capacity);
            products.push_back(newProduct);
        }
        file.close();
    } else {
        cout << "No existing data found." << endl;
    }
}

void Manager::writeToFile() const {
    ofstream file(FILENAME);
    if (file.is_open()) {
        for (const auto& product : products) {
            file << product.getName() << ',' << product.getCategory() << ',' << product.getPrice() << ',' << product.getCapacity() << '\n';
        }
        file.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

void Manager::removeProductCapacity(const std::string& productName, int quantity) {
    for (auto& product : products) {
        if (product.getName() == productName) {
           
            int newCapacity = product.getCapacity() - quantity;
            
            
            newCapacity = (newCapacity < 0) ? 0 : newCapacity;
            
            
            product.setCapacity(newCapacity);

            
            updateProductFile();
          
            return; 
        }
    }

    
    cout << "Product not found." << endl;
}



void Manager::readShelfFile() const {
    ifstream file(SHELF_FILE);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    
    } else {
        cout << "Unable to open shelf data file." << endl;
    }
}

void Manager::displayShelf() const {
	
    cout << "Shelf Contents:" << endl;
    readShelfFile();
}

void Manager::updateProductFile() const {
    
    ofstream file(FILENAME, ios::trunc);

    
    if (!file.is_open()) {
        cerr << "Unable to open product data file for updating." << endl;
        return; 
    }

    for (const auto& product : products) {
        file << product.getName() << ',' << product.getCategory() << ',' << product.getPrice() << ',' << product.getCapacity() << '\n';
    }

    file.close();
}


void Manager::updateShelfFile(const Product& updatedProduct) {
    
    ifstream file(SHELF_FILE);

    if (!file.is_open()) {
        cerr << "Unable to open shelf data file for updating." << endl;
        return;
    }

    
    vector<string> updatedShelfData;

    string currentCategory;

    
    string line;
    while (getline(file, line)) {
        
        if (line.empty() || line.find(',') == string::npos) {
            currentCategory = line; 
            updatedShelfData.push_back(line);
        } else {
           
            istringstream ss(line);
            string productName;
            string capacity;

            getline(ss, productName, ',');
            getline(ss, capacity, ',');

            if (productName == updatedProduct.getName()) {
                
                int updatedCapacity = stoi(capacity) - updatedProduct.getCapacity();
                updatedShelfData.push_back(updatedProduct.getName() + ", " + to_string(updatedCapacity));
            } else {
                    updatedShelfData.push_back(line);
            }
        }
    }

    file.close();

    ofstream outFile(SHELF_FILE, ios::trunc);

     if (!outFile.is_open()) {
        cerr << "Unable to open shelf data file for updating." << endl;
        return;
    }

    for (const auto& data : updatedShelfData) {
        outFile << data << '\n';
    }
    
	outFile.close();

    if (outFile.fail()) {
        cerr << "Error updating shelf data file." << endl;
        perror("Error");
    }
}



int Manager::getProductCapacity(const string& productName) const {
    
    Product product = findProduct(productName);
    if (product.getName() != "Not Found") {
        return product.getCapacity();
    } else {
        return 0; 
    }
}

