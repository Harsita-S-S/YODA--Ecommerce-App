#ifndef CART_H
#define CART_H

#include "product.h"
#include <vector>
using namespace std;

class Cart {
private:
    vector<Product> products;
    vector<int> quantities;
public:
    Cart();
    void addProduct(const Product &product, int quantity);
    void removeProduct(const string &productName);
    void updateQuantity(const string &productName, int newQuantity);
    vector<Product> getCartItems() const;
    double getTotalPrice() const;
    vector<int> getQuantities()const;
};

#endif
