#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include "Product.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class ProductWidget : public QWidget {
    Q_OBJECT
private:
    Product product;
    int quantity;
    QLabel *nameLabel;
    QLabel *priceLabel;
    QLabel *quantityLabel;
    QPushButton *increaseButton;
    QPushButton *decreaseButton;
    QPushButton *removeButton;
    QHBoxLayout *layout;

public:
    ProductWidget(const Product &product, int quantity, QWidget *parent = nullptr);
    ~ProductWidget();
    Product getProduct() const;
    std::string getProductName() const;
    int getQuantity() const;

private:
    void updateQuantityLabel();

signals:
    void quantityChanged(const std::string &productName, int newQuantity);
    void productRemoved(const std::string &productName);

private slots:
    void onIncreaseQuantity();
    void onDecreaseQuantity();
    void onRemoveProduct();
};

#endif
