#include "cartviewwindow.h"
#include "productwidget.h"
#include "checkoutwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QSpacerItem>
#include <QDebug>

CartViewWindow::CartViewWindow(Cart *cart, QWidget *parent): QWidget(parent), cart(cart), checkoutWindow(nullptr)
{
    headerLabel = new QLabel("Your Cart", this);
    headerLabel->setAlignment(Qt::AlignCenter);
    headerLabel->setStyleSheet("font-size: 24px; font-weight: bold; padding: 10px;");

    scrollArea = new QScrollArea(this);
    scrollContent = new QWidget();
    scrollLayout = new QVBoxLayout(scrollContent);
    scrollContent->setLayout(scrollLayout);

    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    totalLabel = new QLabel("Total: $0", this);
    totalLabel->setAlignment(Qt::AlignRight);
    totalLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px 20px;");

    nextButton = new QPushButton("Next", this);
    nextButton->setFixedHeight(60);
    nextButton->setMinimumWidth(150);
    nextButton->setStyleSheet("font-size: 16px; padding: 8px 20px; margin: 10px 20px; "
                              "background-color: #4CAF50; color: white; border: none; border-radius: 5px;");

    connect(nextButton, &QPushButton::clicked, this, &CartViewWindow::onNextClicked);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(headerLabel);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(totalLabel);
    mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addWidget(nextButton, 0, Qt::AlignRight);
    setLayout(mainLayout);

    setMinimumSize(450, 300);

    updateCartDisplay();
}

CartViewWindow::~CartViewWindow()
{
    for (ProductWidget *widget : productWidgets)
    {
        delete widget;
    }
}

void CartViewWindow::updateCartDisplay() {
    for (ProductWidget *widget : productWidgets) {
        scrollLayout->removeWidget(widget);
        delete widget;
    }
    productWidgets.clear();

    std::vector<Product> cartItems = cart->getCartItems();
    std::vector<int> quantities = cart->getQuantities();
    for (size_t i = 0; i < cartItems.size(); ++i) {
        ProductWidget *productWidget = new ProductWidget(cartItems[i], quantities[i], this);
        scrollLayout->addWidget(productWidget);
        productWidgets.push_back(productWidget);
        connect(productWidget, &ProductWidget::quantityChanged, this, &CartViewWindow::onProductQuantityChanged);
        connect(productWidget, &ProductWidget::productRemoved, this, &CartViewWindow::onProductRemoved);
    }

    updateTotalAmount();
    if (cartItems.empty())
    {
        nextButton->setEnabled(false);
        nextButton->setStyleSheet("font-size: 16px; padding: 8px 20px; margin: 10px 20px; ""background-color: grey; color: white; border: none; border-radius: 5px;");
    }
    else
    {
        nextButton->setEnabled(true);
        nextButton->setStyleSheet("font-size: 16px; padding: 8px 20px; margin: 10px 20px; " "background-color: #4CAF50; color: white; border: none; border-radius: 5px;");
    }
}

void CartViewWindow::onProductQuantityChanged(const std::string &productName, int newQuantity) {
    cart->updateQuantity(productName, newQuantity);
    updateCartDisplay();
}

void CartViewWindow::onProductRemoved(const std::string &productName) {
    cart->removeProduct(productName);
    updateCartDisplay();
}

void CartViewWindow::updateTotalAmount()
{
    double total = cart->getTotalPrice();
    totalLabel->setText("Total : $" + QString::number(total, 'f', 2));
}

void CartViewWindow::onNextClicked() {
    qDebug() << "Next button clicked, creating CheckoutWindow";
    checkoutWindow = new CheckoutWindow(cart, nullptr);
    checkoutWindow->show();
    qDebug() << "CheckoutWindow shown, closing CartViewWindow";
    this->close();
}
