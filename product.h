#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

using namespace std;

class Product
{
private:
    string name;
    double price;
    string category;
    string details;

public:
    Product();
    Product(string n, double p, string c, string d);
    Product(const Product &others);
    void setName(string n);
    void setPrice(double p);
    void setCategory(string c);
    virtual void setDetails(string d);
    string getName() const;
    double getPrice() const;
    string getCategory() const;
    virtual string getDetails() const;
    virtual string getWoodType() const;
    virtual string getSpecifications() const;
    virtual string getSize()const;
    virtual string getMaterial()const;
    virtual string getType()const;
    virtual string getBrand()const;
    virtual string getCompany() const;
    friend ostream& operator<<(ostream& out,const Product &p);
};

#endif
