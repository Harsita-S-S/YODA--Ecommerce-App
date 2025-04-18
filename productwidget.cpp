#include "productwidget.h"
#include <QString>

ProductWidget::ProductWidget(const Product &product, int quantity, QWidget *parent)
    : QWidget(parent), product(product), quantity(quantity) {
    nameLabel = new QLabel(QString::fromStdString(product.getName()));
    priceLabel = new QLabel("$" + QString::number(product.getPrice() * quantity, 'f', 2));
    quantityLabel = new QLabel(QString::number(quantity));

    increaseButton = new QPushButton("+");
    decreaseButton = new QPushButton("-");
    removeButton = new QPushButton("Remove");

    connect(increaseButton, &QPushButton::clicked, this, &ProductWidget::onIncreaseQuantity);
    connect(decreaseButton, &QPushButton::clicked, this, &ProductWidget::onDecreaseQuantity);
    connect(removeButton, &QPushButton::clicked, this, &ProductWidget::onRemoveProduct);

    layout = new QHBoxLayout();
    layout->addWidget(nameLabel);
    layout->addWidget(priceLabel);
    layout->addWidget(quantityLabel);
    layout->addWidget(increaseButton);
    layout->addWidget(decreaseButton);
    layout->addWidget(removeButton);

    setLayout(layout);
}

ProductWidget::~ProductWidget() {}

Product ProductWidget::getProduct() const {
    return product;
}

std::string ProductWidget::getProductName() const {
    return product.getName();
}

int ProductWidget::getQuantity() const {
    return quantity;
}

void ProductWidget::updateQuantityLabel() {
    quantityLabel->setText(QString::number(quantity));
    double totalPrice = product.getPrice() * quantity;
    priceLabel->setText("$" + QString::number(totalPrice, 'f', 2));
}

void ProductWidget::onIncreaseQuantity() {
    quantity++;
    updateQuantityLabel();
    emit quantityChanged(product.getName(), quantity);
}

void ProductWidget::onDecreaseQuantity() {
    if (quantity > 0) {
        quantity--;
        updateQuantityLabel();
        emit quantityChanged(product.getName(), quantity);
    }
}

void ProductWidget::onRemoveProduct() {
    emit productRemoved(product.getName());
}
