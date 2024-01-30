#include "batchpack.h"
#include "manager.h"

#include <algorithm>
BatchPack::BatchPack() {}


void BatchPack::addOrder(const Product& order) {
    orders.push_back(order);
}

void BatchPack::createBatch() {
    batches.push_back(orders);
    orders.clear();
}

void BatchPack::displayBatch() const {
    displayBatches();
}

void BatchPack::prepareBatch() {
     
    string productName;
    while (true) {
        cout << "Enter the name of the product to prepare (or 'done' to finish): ";
        cin >> productName;

        if (productName == "done") {
            break;
        }

        // Se�ilen �r�n� ve miktar�n� orders listesinden bul
        auto it = std::find_if(orders.begin(), orders.end(),
                               [productName](const Product& order) { return order.getName() == productName; });

        if (it != orders.end()) {
            // E�er stok yetersizse, uyar� ver ve i�lemi iptal et
            if (it->getCapacity() > manager.getProductCapacity(productName)) {
                cout << "Warning: Insufficient stock for product '" << productName << "'. Order preparation aborted.\n";
                continue;
            }

            // Se�ilen �r�n�n stoktan d���lmesi
            manager.removeProductCapacity(productName, it->getCapacity());

            // Sipari�i orders listesinden sil
            orders.erase(it);

            cout << "Order prepared successfully!" << endl;
        } else {
            cout << "Order not found." << endl;
        }
    }

    // BatchPack s�n�f�n� kullanarak haz�rlanan sipari�leri i�le
    createBatch();

    cout << "Order(s) prepared successfully!" << endl;
}



void BatchPack::displayBatches() const {
    // batches vekt�r�ndeki her bir batch'i g�ster
    for (size_t i = 0; i < batches.size(); ++i) {
        cout << "Batch " << i + 1 << ":" << endl;
        for (const auto& order : batches[i]) {
            order.displayProduct();  
        }
    }
}


