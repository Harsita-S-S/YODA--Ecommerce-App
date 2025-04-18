#ifndef ELECTRONICS_H
#define ELECTRONICS_H
#include <string>
#include "product.h"
using namespace std;

class Electronics : public Product
{
private:
    string company;
    string type;
    string specifications;

public:
    Electronics();
    Electronics(string n, double p, string c, string d, string comp, string t, string s);
    Electronics(const Electronics &others);

    void setCompany(string c);
    void setType(string t);
    void setSpecifications(string s);

    string getCompany() const;
    string getType() const;
    string getSpecifications() const;
};

#endif
