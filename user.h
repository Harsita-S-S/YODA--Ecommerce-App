#ifndef USER_H
#define USER_H
#include "cart.h"
#include <string>

using namespace std;

class User
{
private:
    string name;
    string password;
    Cart cart;
    string email;
    string location;

public:
    User();
    User(string n,string pwd,Cart cart);
    User(const User &others);

    void setName(string n);
    void setPassword(string p);
    void setCart(Cart cart);
    void setLocation(string loc);
    void setEmail(string mail);

    string getName();
    string getPassword();
    Cart* getCart();
};

#endif // USER_H
