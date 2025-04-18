#ifndef CARTVIEWWINDOW_H
#define CARTVIEWWINDOW_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <vector>
#include "cart.h"
#include "productwidget.h"
#include "checkoutwindow.h"
class CartViewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CartViewWindow(Cart *cart, QWidget *parent = nullptr);
    ~CartViewWindow();

public slots:
    void onProductQuantityChanged(const std::string &productName, int newQuantity);
    void onProductRemoved(const std::string &productName);
    void onNextClicked();

private:
    void updateCartDisplay();
    void updateTotalAmount();

    Cart *cart;
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QWidget *scrollContent;
    QVBoxLayout *scrollLayout;
    std::vector<ProductWidget *> productWidgets;

    QLabel *headerLabel;
    QLabel *totalLabel;

    QPushButton *nextButton;
    CheckoutWindow *checkoutWindow;
};

#endif
