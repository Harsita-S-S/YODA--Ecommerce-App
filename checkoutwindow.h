#ifndef CHECKOUTWINDOW_H
#define CHECKOUTWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include "cart.h"

class CheckoutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CheckoutWindow(Cart *cart, QWidget *parent = nullptr);
    ~CheckoutWindow();

private slots:
    void onProceedClicked();

private:
    void populateTable(const std::vector<Product> &cartItems,const std::vector<int> &quantities);
    QTableWidget *tableWidget;
    QLabel *labelTotal;
    QPushButton *buttonProceed;
    Cart *cart;

};

#endif
