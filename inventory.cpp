#include "inventory.h"

Inventory::Inventory() {}

Inventory::~Inventory()
{
    for (int i = 0; i < products.size(); i++)
    {
        delete products[i];
    }
    products.clear();
}

void Inventory::addProduct(Product* p)
{
    products.push_back(p);
}

void Inventory::removeProduct(string name)
{
    for (int i = 0; i < products.size(); i++)
    {
        if (products[i]->getName() == name)
        {
            delete products[i];
            for (int j = i; j < products.size() - 1; j++)
            {
                products[j] = products[j + 1];
            }
            products.pop_back();
        }
    }
}

void Inventory::updateProduct(string name, double pr, string cat, string details)
{
    for (int i = 0; i < products.size(); i++)
    {
        if (products[i]->getName() == name)
        {
            products[i]->setPrice(pr);
            products[i]->setCategory(cat);
            products[i]->setDetails(details);
        }
    }
}

Product* Inventory::getProduct(string name)
{
    for (int i = 0; i < products.size(); i++)
    {
        if (products[i]->getName() == name)
        {
            return products[i];
        }
    }
    return nullptr;
}

vector<Product*> Inventory::getAllProducts() const
{
    return products;
}

