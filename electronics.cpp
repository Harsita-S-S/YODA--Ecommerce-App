#include <string>
#include "product.h"
#include "electronics.h"
using namespace std;
Electronics::Electronics(): Product()
{
    company = "";
    type = "";
    specifications = "";
}

Electronics::Electronics(string n, double p, string c, string d, string comp, string t, string s): Product(n, p, c, d)
{
    company = comp;
    type = t;
    specifications = s;
}

Electronics::Electronics(const Electronics &others): Product(others)
{
    company = others.company;
    type = others.type;
    specifications = others.specifications;
}

void Electronics::setCompany(string c)
{
    company = c;
}

void Electronics::setType(string t)
{
    type = t;
}

void Electronics::setSpecifications(string s)
{
    specifications = s;
}

string Electronics::getCompany() const
{
    return company;
}

string Electronics::getType() const
{
    return type;
}

string Electronics::getSpecifications() const
{
    return specifications;
}
