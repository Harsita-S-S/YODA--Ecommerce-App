#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED
#include "product.h"
#include <vector>
using namespace std;

class Inventory
{
private:
    vector<Product*> products;

public:
    Inventory();
    ~Inventory();
    void addProduct(Product* p);
    void removeProduct(string name);
    void updateProduct(string name, double pr, string cat, string details);
    Product* getProduct(string name);
    vector<Product*> getAllProducts() const;
};

#endif
