#ifndef FURNITURE_H_INCLUDED
#define FURNITURE_H_INCLUDED
#include "product.h"
#include <string>
using namespace std;
class Furniture:public Product
{
private:
    string woodType;
    string type;
    string specifications;
public:
    Furniture();
    Furniture(Furniture const &others);
    Furniture(string n, double p, string c, string d,string w,string t,string s);
    void setWoodType(string w);
    void setType(string t);
    void setSpecifications(string s);
    string getWoodType() const;
    string getType() const;
    string getSpecifications() const;
};
#endif
