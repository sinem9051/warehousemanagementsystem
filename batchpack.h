#ifndef BATCHPACK_H
#define BATCHPACK_H


#include <iostream>
#include <vector>
#include "product.h"  
#include "manager.h" 


class BatchPack {
public:
    BatchPack();

    // Sipariþ eklemek için fonksiyon
    void addOrder(const Product& order);

    // Batch oluþturmak için fonksiyon
    void createBatch();

    // Batch içindeki ürünleri göstermek için fonksiyon
    void displayBatch() const;

    // Batch içindeki ürünleri hazýrlamak için fonksiyon
    void prepareBatch();
    

    

private:
	
	 Manager manager; 
    // Sipariþleri içeren vektör
    vector<Product> orders;

    // Oluþturulan batch'leri içeren vektör
    vector<std::vector<Product>> batches;

    // Oluþturulan batch'leri gösteren fonksiyon
    void displayBatches() const;
    

    
};

#endif // BATCHPACK_H

