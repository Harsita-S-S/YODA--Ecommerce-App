#include "cart.h"

Cart::Cart() {}

void Cart::addProduct(const Product &product, int quantity)
{
    for (size_t i = 0; i < products.size(); ++i)
    {
        if (products[i].getName() == product.getName())
        {
            quantities[i] += quantity;
            return;
        }
    }
    products.push_back(product);
    quantities.push_back(quantity);
}

void Cart::removeProduct(const string &productName)
{
    for (size_t i = 0; i < products.size(); ++i)
    {
        if (products[i].getName() == productName)
        {
            products.erase(products.begin() + i);
            quantities.erase(quantities.begin() + i);
            return;
        }
    }
}

void Cart::updateQuantity(const std::string &productName, int newQuantity) {
    for (size_t i = 0; i < products.size(); ++i) {
        if (products[i].getName() == productName) {
            if (newQuantity <= 0) {
                products.erase(products.begin() + i);
                quantities.erase(quantities.begin() + i);
            } else {
                quantities[i] = newQuantity;
            }
            return;
        }
    }
}

vector<Product> Cart::getCartItems() const
{
    return products;
}
vector<int> Cart::getQuantities()const
{
    return quantities;
}
double Cart::getTotalPrice() const
{
    double total = 0;
    for (size_t i = 0; i < products.size(); ++i)
    {
        total += products[i].getPrice() * quantities[i];
    }
    return total;
}
