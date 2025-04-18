#include "user.h"

User::User()
{
    name="";
    password="";
}
User::User(string n,string pwd,Cart cart)
{
    name=n;
    password=pwd;
    this->cart=cart;
}
User::User(const User &others)
{
    this->name=others.name;
    this->password=others.password;
    this->cart=others.cart;
}
void User::setName(string n) {
    name = n;
}

void User::setPassword(string p) {
    password = p;
}

void User::setCart(Cart cart) {
    this->cart = cart;
}


string User::getName() {
    return name;
}

string User::getPassword() {
    return password;
}

Cart* User::getCart() {
    return &cart;
}



