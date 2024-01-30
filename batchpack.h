#ifndef BATCHPACK_H
#define BATCHPACK_H


#include <iostream>
#include <vector>
#include "product.h"  
#include "manager.h" 


class BatchPack {
public:
    BatchPack();

    // Sipari� eklemek i�in fonksiyon
    void addOrder(const Product& order);

    // Batch olu�turmak i�in fonksiyon
    void createBatch();

    // Batch i�indeki �r�nleri g�stermek i�in fonksiyon
    void displayBatch() const;

    // Batch i�indeki �r�nleri haz�rlamak i�in fonksiyon
    void prepareBatch();
    

    

private:
	
	 Manager manager; 
    // Sipari�leri i�eren vekt�r
    vector<Product> orders;

    // Olu�turulan batch'leri i�eren vekt�r
    vector<std::vector<Product>> batches;

    // Olu�turulan batch'leri g�steren fonksiyon
    void displayBatches() const;
    

    
};

#endif // BATCHPACK_H

