#ifndef CLOTHES_H
#define CLOTHES_H

#include "product.h"
#include <string>

using namespace std;

class Clothes : public Product
{
private:
    string size;
    string material;
    string type;
    string brand;

public:
    Clothes();
    Clothes(string n, double p, string c, string d, string s, string m, string t, string b);
    Clothes(const Clothes &others);
    void setSize(string s);
    void setMaterial(string m);
    void setType(string t);
    void setBrand(string b);
    string getSize()const;
    string getMaterial()const;
    string getType()const;
    string getBrand()const;
};

#endif
