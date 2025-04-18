#include <iostream>
#include <string>
#include "product.h"
using namespace std;

Product::Product()
{
    name = "";
    price = 0.0;
    category = "";
    details = "";
}
Product::Product(const Product &others)
{
    name = others.name;
    price = others.price;
    category = others.category;
    details = others.details;
}
Product::Product(string n, double p, string c, string d)
{
    name = n;
    price = p;

    category = c;
    details = d;
}

void Product::setName(string n)
{
    name = n;
}

void Product::setPrice(double p)
{
    price = p;
}


void Product::setCategory(string c)
{
    category = c;
}

void Product::setDetails(string d)
{
    details = d;
}

string Product::getName() const
{
    return name;
}

double Product::getPrice()const
{
    return price;
}

string Product::getCategory()const
{
    return category;
}

string Product::getDetails()const
{
    return details;
}


string Product::getWoodType() const { return ""; }

string Product::getSpecifications() const { return ""; }

string Product::getSize() const { return ""; }

string Product::getMaterial() const { return ""; }

string Product::getType() const { return ""; }

string Product::getBrand() const { return ""; }

string Product::getCompany() const { return ""; }

ostream& operator<<(ostream &out,const Product &p) {
    out<<"Name: "<<p.getName()<<endl;
    out<<"Price: "<<p.getPrice()<<endl;
    out<<"Category: "<<p.getCategory()<<endl;
    out<<"Details: "<<p.getDetails()<<endl;
    return out;
}
