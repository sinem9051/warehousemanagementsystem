#include "employee.h"
#include "BatchPack.h"
#include "product.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

const string ORDERS_FILE = "orders.txt";  

Employee::Employee(const Manager& manager) : manager(manager) {}



void Employee::createOrder() {
    cout << "Creating order..." << endl;
	manager.readFromFile();
    
    cout << "Available Products:" << endl;
   manager.viewProducts();

    string productName;
    int quantity;

    cout << "Enter the name of the product you want to order: ";
    cin >> productName;

    cout << "Enter the quantity you want to order: ";
    cin >> quantity;

    Product selectedProduct = manager.findProduct(productName);
    if (selectedProduct.getName() != "Not Found") {
        
        int productCapacity = manager.getProductCapacity(productName);

        if (quantity > productCapacity) {
            cout << "Error: Insufficient product capacity for order '" << productName << "'. Order creation failed.\n";
        } else {
           
            selectedProduct.setCapacity(quantity);
            orders.push_back(selectedProduct);
           
            writeOrdersToFile();

            cout << "Order created successfully!" << endl;
        }
    } else {
        cout << "Product not found. Order creation failed." << endl;
    }
}
    



void Employee::viewOrders() const {
    cout << "Viewing orders..." << endl;

    if (orders.empty()) {
        cout << "No orders available." << endl;
        return;
    }

    cout << "Order List:" << endl;
    for (const auto& order : orders) {
        cout << "Name: " << order.getName() << ", Category: " << order.getCategory()
             << ", Price: " << order.getPrice() << ", Quantity to create: " << order.getCapacity() << endl;
    }


}


void Employee::prepareOrder() {
    cout << "Preparing order..." << endl;

    // BatchPack sýnýfýný kullanarak sipariþleri hazýrla
    BatchPack batchPack;

    string productName;
    bool continueEntering = true;

    // KullanÄ±cÄ±dan hazÄorlanacak sipariþi seçmesini iste
    while (continueEntering) {
        cout << "Enter the name of the product to prepare (or 'done' to finish): ";
        cin >> productName;

        if (productName == "done") {
            if (continueEntering) {
                continueEntering = false;
            } else {
                break;  
            }
        } else {
            // Seçilen ürünü ve miktarýný orders listesinden bul
            auto it = std::find_if(orders.begin(), orders.end(),
                                   [productName](const Product& order) { return order.getName() == productName; });

            if (it != orders.end()) {
                batchPack.addOrder(*it);
                orders.erase(it);

                // Yönetici sýnýfýndaki ürün miktarýný güncelle
                manager.removeProductCapacity(productName, it->getCapacity());
                
                 // Shelf dosyasýný güncelle
                manager.updateShelfFile(*it);
                
            } else {
                cout << "Order not found." << endl;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Buffer'dan gereksiz giriþleri temizle
    }

    // BatchPack sýnýfýný kullanarak hazýrlanan sipariþleri iþle
    batchPack.prepareBatch();

    // Güncellenen sipariþleri dosyaya yaz
    writeOrdersToFile();

    cout << "Order(s) prepared successfully!" << endl;
}

void Employee::displayProduct(const Product& product) const {
    product.displayProduct(); 
}
void Employee::writeOrdersToFile() const {
    ofstream file(ORDERS_FILE, ios::trunc);  
    if (file.is_open()) {
        for (const auto& order : orders) {
            file << order.getName() << ',' << order.getCategory() << ',' << order.getPrice() << ',' << order.getCapacity() << '\n';
        }
        file.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

void Employee::readOrdersFromFile() {
	
    ifstream file(ORDERS_FILE);
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

            Product newOrder(name, category, price, capacity);
            orders.push_back(newOrder);
        }
        file.close();
    } else {
        cout << "No existing orders found." << endl;
    }

}

