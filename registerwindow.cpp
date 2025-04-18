#include "registerwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <qpushbutton.h>
#include <fstream>

using namespace std;
RegisterWindow::RegisterWindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300,400);
    addressHeader = new QLabel("Sign in Details", this);
    fullName = new QLabel("Full Name", this);
    streetAddress = new QLabel("Street Address", this);
    password = new QLabel("Password", this);
    email = new QLabel("Email", this);
    phoneNumber = new QLabel("Phone Number", this);

    fullNameEdit = new QLineEdit(this);
    streetAddressEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    phoneNumberEdit = new QLineEdit(this);

    QPushButton *ok = new QPushButton("OK",this);
    QPushButton *cancel = new QPushButton("Cancel",this);
    connect(ok, &QPushButton::clicked, this, &RegisterWindow::saveDetails);
    connect(cancel, &QPushButton::clicked, this, &RegisterWindow::cancelDetails);

    formLayout = new QVBoxLayout();
    formLayout->addWidget(addressHeader);
    formLayout->addWidget(fullName);
    formLayout->addWidget(fullNameEdit);
    formLayout->addWidget(password);
    formLayout->addWidget(passwordEdit);
    formLayout->addWidget(streetAddress);
    formLayout->addWidget(streetAddressEdit);

    formLayout->addWidget(email);
    formLayout->addWidget(emailEdit);
    formLayout->addWidget(phoneNumber);
    formLayout->addWidget(phoneNumberEdit);
    formLayout->addWidget(ok);
    formLayout->addWidget(cancel);
    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(formLayout);

    setLayout(mainLayout);

}
void RegisterWindow::saveDetails()
{
    ifstream f1;
    f1.open(R"(C:\Users\kalal\OneDrive\Documents\LoginPage\UserDetails.txt)");
    while(f1)
    {
        string data;
        getline(f1,data);
        QString user = QString::fromStdString(data);
        QStringList details = user.split(",");
        if(details[0]==fullNameEdit->text())
        {
            QMessageBox::warning(this, "Registration Failed", "Username already taken.");
            f1.close();
            return;
        }
    }
    f1.close();
    ofstream fh;
    fh.open(R"(C:\Users\kalal\OneDrive\Documents\LoginPage\UserDetails.txt)",ios::app);
    string name = fullNameEdit->text().toStdString();
    string address = streetAddressEdit->text().toStdString();
    string password = passwordEdit->text().toStdString();
    string mail = emailEdit->text().toStdString();
    string phonenum = phoneNumberEdit->text().toStdString();
    fh << name << ',' << password << ',' << address << ',' << mail << ',' << phonenum << '\n';
    fh.close();
    this->close();
}
void RegisterWindow::cancelDetails()
{
    this->close();
}
RegisterWindow::~RegisterWindow() {}
