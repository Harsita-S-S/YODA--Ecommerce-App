#include <string>
#include "product.h"
#include "clothes.h"
using namespace std;

Clothes::Clothes(): Product()
{
    size = "";
    material = "";
    type = "";
    brand = "";
}

Clothes::Clothes(string n, double p, string c, string d, string s, string t, string m, string b): Product(n, p, c, d)
{
    size = s;
    material = m;
    type = t;
    brand = b;
}

Clothes::Clothes(const Clothes &others): Product(others)
{
    size = others.size;
    material = others.material;
    type = others.type;
    brand = others.brand;
}

void Clothes::setSize(string s)
{
    size = s;
}

void Clothes::setMaterial(string m)
{
    material = m;
}

void Clothes::setType(string t)
{
    type = t;
}

void Clothes::setBrand(string b)
{
    brand = b;
}

string Clothes::getSize() const
{
    return size;
}

string Clothes::getMaterial() const
{
    return material;
}

string Clothes::getType()const
{
    return type;
}

string Clothes::getBrand()const
{
    return brand;
}
