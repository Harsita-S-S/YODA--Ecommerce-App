#include "onlinepaymentwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFont>
#include <fstream>
using namespace std;
OnlinePaymentWindow::OnlinePaymentWindow(int count,QWidget *parent): QWidget(parent)
{
    setWindowTitle("Payment Gateway");
    setFixedSize(350, 250);

    QLabel *heading = new QLabel("Payment Gateway", this);
    QFont font;
    font.setPointSize(16);
    font.setBold(true);
    heading->setFont(font);
    heading->setAlignment(Qt::AlignCenter);

    QLabel *usernameLabel = new QLabel("Username:", this);
    usernameEdit = new QLineEdit(this);

    QVBoxLayout *userLayout = new QVBoxLayout();
    userLayout->addWidget(usernameLabel);
    userLayout->addWidget(usernameEdit);

    QLabel *passwordLabel = new QLabel("Password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    QVBoxLayout *passLayout = new QVBoxLayout();
    passLayout->addWidget(passwordLabel);
    passLayout->addWidget(passwordEdit);

    payButton = new QPushButton("Pay Now", this);
    connect(payButton, &QPushButton::clicked, this,[=]{handlePayment(count);});

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(heading);
    mainLayout->addLayout(userLayout);
    mainLayout->addLayout(passLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(payButton, 0, Qt::AlignHCenter);

    setLayout(mainLayout);
}

void OnlinePaymentWindow::handlePayment(int count)
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
        return;
    }

    ifstream fh;



    fh.open(R"(C:\Users\kalal\OneDrive\Documents\LoginPage\UserDetails.txt)");
    string data;
    QStringList details;
    for(int i=0;i<count;i++)
    {
        getline(fh,data);
        QString user = QString::fromStdString(data);
        details = user.split(",");
    }
    if(details[0]==username && details[1]==password)
    {
        QMessageBox::information(this, "Payment Success", "Payment successful! Thank you.");
        this->close();
    }
    else
    {
        QMessageBox::information(this, "Payment Failed", "Invalid Password or Username");
    }


}
