#include "deliveryandpayment.h"
#include "onlinepaymentwindow.h"
#include <QHBoxLayout>
#include <QSplitter>
#include <QGuiApplication>
#include <QScreen>
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QDebug>
#include <fstream>

DeliveryAndPayment::DeliveryAndPayment(Cart *cart, QWidget *parent)
    : QDialog(parent), cart(cart)
{
    setWindowTitle("Checkout");
    setFixedSize(900, 500);
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->setStyleSheet("QSplitter::handle { background-color: #ccc; width: 2px; }");

    // Address section
    QWidget *addressWidget = new QWidget();
    QVBoxLayout *addressLayout = new QVBoxLayout(addressWidget);
    addressLayout->setSpacing(10);

    QLabel *addressHeader = new QLabel("Address Details");
    addressHeader->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 10px;");
    addressLayout->addWidget(addressHeader, 0, Qt::AlignCenter);

    fullNameEdit = new QLineEdit();
    fullNameEdit->setStyleSheet("padding: 6px; border: 1px solid #ccc; border-radius: 4px;");
    streetAddressEdit = new QLineEdit();
    streetAddressEdit->setStyleSheet("padding: 6px; border: 1px solid #ccc; border-radius: 4px;");

    phoneNumberEdit = new QLineEdit();
    phoneNumberEdit->setStyleSheet("padding: 6px; border: 1px solid #ccc; border-radius: 4px;");

    addressLayout->addWidget(new QLabel("Full Name"));
    addressLayout->addWidget(fullNameEdit);
    addressLayout->addWidget(new QLabel("Street Address"));
    addressLayout->addWidget(streetAddressEdit);

    addressLayout->addWidget(new QLabel("Phone Number"));
    addressLayout->addWidget(phoneNumberEdit);

    ifstream f1;

    count=0;

    f1.open(R"(C:\Users\kalal\OneDrive\Documents\LoginPage\UserDetails.txt)");
    while(f1)
    {
        string data;
        getline(f1,data);
        QString user = QString::fromStdString(data);
        QStringList details = user.split(",");
        if(details.size()==1)
        {

            count=details[0].toInt();
            break;
        }


    }
    f1.close();
    ifstream fh;



    f1.open(R"(C:\Users\kalal\OneDrive\Documents\LoginPage\UserDetails.txt)");
    string data;
    QStringList details;
    for(int i=0;i<count;i++)
    {
        getline(f1,data);
        QString user = QString::fromStdString(data);
        details = user.split(",");
    }
    fullNameEdit->setText(details[0]);
    streetAddressEdit->setText(details[2]);
    phoneNumberEdit->setText(details[4]);
    fh.close();

    ifstream f2(R"(C:\Users\kalal\OneDrive\Documents\LoginPage\UserDetails.txt)");
    vector<string> lines;
    string line;

    while(getline(f2,line))
    {
        lines.push_back(line);
    }
    f2.close();

    lines.pop_back();

    ofstream fh3(R"(C:\Users\kalal\OneDrive\Documents\LoginPage\UserDetails.txt)",std::ios::trunc);
    for(int i=0;i<lines.size();i++)
    {
        fh3<<lines[i]<<'\n';
    }
    fh3.close();


    addressLayout->addStretch();

    splitter->addWidget(addressWidget);

    QWidget *paymentWidget = new QWidget();
    paymentWidget->setStyleSheet("background-color: #1e1e1e; color: white; border: 2px solid #333; border-radius: 10px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.3);");
    QVBoxLayout *paymentLayout = new QVBoxLayout(paymentWidget);
    paymentLayout->setContentsMargins(20, 20, 20, 20);
    paymentLayout->setSpacing(10);
    paymentLayout->addStretch();

    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setStyleSheet("border: none;");
    scrollArea->setMaximumHeight(280);

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    scrollLayout->addStretch();

    orderSummaryWidget = new QWidget();
    orderSummaryWidget->setStyleSheet("background-color: #2c2c2c; border-radius: 8px; padding: 12px; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);");
    QVBoxLayout *orderSummaryLayout = new QVBoxLayout(orderSummaryWidget);
    orderSummaryLayout->setContentsMargins(0, 0, 0, 0);
    orderSummaryLayout->setSpacing(8);

    orderSummaryLabel = new QLabel("ORDER SUMMARY");
    orderSummaryLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #4CAF50; padding-bottom: 5px;");
    orderSummaryLabel->setAlignment(Qt::AlignCenter);

    QString summaryText = "Items:\n";
    double total = 0;
    int totalItems=0;
    const auto &cartItems = cart->getCartItems();
    const auto &quantities = cart->getQuantities();


    for (int i = 0; i < cartItems.size(); i++)
    {
        summaryText += QString::fromStdString(cartItems[i].getName())+" x "+QString::number(quantities[i])+"\n";
        total += cartItems[i].getPrice()*quantities[i];
        totalItems += quantities[i];
    }
    summaryText += "\nTotal Items: "+QString::number(totalItems);
    summaryText += "\nTotal: $"+QString::number(total,'f',2);


    orderSummaryEdit = new QTextEdit();
    orderSummaryEdit->setText(summaryText);
    orderSummaryEdit->setReadOnly(true);
    orderSummaryEdit->setStyleSheet("background-color: #f0f0f0; color: #333; border: none; padding: 8px; border-radius: 4px; font-size: 14px;");
    orderSummaryEdit->setFixedHeight(80);

    orderSummaryLayout->addWidget(orderSummaryLabel);
    orderSummaryLayout->addWidget(orderSummaryEdit);
    scrollLayout->addWidget(orderSummaryWidget);

    paymentMethodWidget = new QWidget();
    paymentMethodWidget->setStyleSheet("background-color: #2c2c2c; border-radius: 8px; padding: 12px; box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2); margin-top: 15px;");
    QVBoxLayout *paymentMethodLayout = new QVBoxLayout(paymentMethodWidget);
    paymentMethodLayout->setContentsMargins(0, 0, 0, 0);
    paymentMethodLayout->setSpacing(8);

    paymentMethodLabel = new QLabel("Payment Method");
    paymentMethodLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: white; padding-bottom: 5px;");

    paymentComboBox = new QComboBox();
    paymentComboBox->addItem("Online Payment");
    paymentComboBox->addItem("Pay On Delivery");
    paymentComboBox->setStyleSheet("background-color: #333; color: white; padding: 8px; border: 2px solid #4CAF50; border-radius: 4px; font-size: 14px;");

    paymentMethodLayout->addWidget(paymentMethodLabel);
    paymentMethodLayout->addWidget(paymentComboBox);
    scrollLayout->addWidget(paymentMethodWidget);

    scrollArea->setWidget(scrollWidget);


    QHBoxLayout *footerLayout = new QHBoxLayout();
    footerLayout->addStretch();
    footerLayout->setSpacing(10);

    confirmButton = new QPushButton("Confirm Payment");
    confirmButton->setFixedHeight(50);
    confirmButton->setMinimumWidth(220);
    confirmButton->setStyleSheet("font-size: 16px; padding: 10px 20px; ""background-color: #4CAF50; color: white; border: none; border-radius: 8px; "
                                 "box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);");
    connect(confirmButton, &QPushButton::clicked, this, &DeliveryAndPayment::confirmPayment);
    confirmButton->setCursor(Qt::PointingHandCursor);
    confirmButton->setFocusPolicy(Qt::StrongFocus);

    footerLayout->addWidget(confirmButton, 0, Qt::AlignHCenter);
    paymentLayout->addWidget(scrollArea);
    paymentLayout->addLayout(footerLayout);

    splitter->addWidget(paymentWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    mainLayout->addWidget(splitter);
    setLayout(mainLayout);


    QPropertyAnimation *fadeIn = new QPropertyAnimation(this, "windowOpacity");
    fadeIn->setDuration(1000);
    fadeIn->setStartValue(0);
    fadeIn->setEndValue(1);
    fadeIn->start();
}

QString DeliveryAndPayment::getFullName() const
{
    return fullNameEdit->text();
}

QString DeliveryAndPayment::getStreetAddress() const
{
    return streetAddressEdit->text();
}



QString DeliveryAndPayment::getPhoneNumber() const
{
    return phoneNumberEdit->text();
}

bool DeliveryAndPayment::isSaveAddressChecked() const
{
    return saveAddressCheckBox->isChecked();
}

void DeliveryAndPayment::confirmPayment()
{
    QString selectedMethod = paymentComboBox->currentText();
    qDebug() << "Selected Payment Method: " << selectedMethod;

    if (selectedMethod == "Online Payment")
    {
        qDebug() << "Online Payment Selected";

        OnlinePaymentWindow *paymentWindow = new OnlinePaymentWindow(count);
        paymentWindow->setAttribute(Qt::WA_DeleteOnClose);

        this->close();
        paymentWindow->show();
    }
    else if (selectedMethod == "Pay On Delivery")
    {
        qDebug() << "Pay On Delivery Selected";

        QMessageBox::information(this, "Order Confirmed", "Your order has been placed with Pay On Delivery.");

        this->close();
    }
    else
    {
        qDebug() << "Invalid Payment Method";
        QMessageBox::warning(this, "Error", "Please select a valid payment method.");
    }
}

DeliveryAndPayment::~DeliveryAndPayment()
{

}
