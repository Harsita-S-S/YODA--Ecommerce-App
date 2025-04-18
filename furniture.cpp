#include <string>
#include "product.h"
#include "furniture.h"
using namespace std;
Furniture::Furniture():Product()
{
    woodType = "";
    type = "";
    specifications = "";
}

Furniture::Furniture(const Furniture &other):Product(other)
{
    woodType = other.woodType;
    type = other.type;
    specifications = other.specifications;
}

Furniture::Furniture( string n, double p, string c, string d,string w, string t, string s)
    : Product(n, p, c, d)
{
    woodType = w;
    type = t;
    specifications = s;
}

void Furniture::setWoodType(string w)
{
    woodType = w;
}

void Furniture::setType(string t)
{
    type = t;
}

void Furniture::setSpecifications(string s)
{
    specifications = s;
}

string Furniture::getWoodType() const
{
    return woodType;
}

string Furniture::getType() const
{
    return type;
}

string Furniture::getSpecifications() const
{
    return specifications;
}




