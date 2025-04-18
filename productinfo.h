#ifndef PRODUCTINFO_H
#define PRODUCTINFO_H

#include "cart.h"
#include "inventory.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwidget.h>

class ProductInfo: public QWidget
{
    Q_OBJECT
public:
    explicit ProductInfo(Inventory &inventory, Cart &finalcart, string name="", QWidget *parent=nullptr);
private:
    Inventory inventory;
    string productName;
    QPushButton *cart;
    QPushButton *plus;
    QPushButton *minus;
    QPushButton *back_submit;
    QPushButton *submit;
    QLineEdit *quantity;
    Cart &finalCart;
private slots:
    void cartClick(QWidget* container, QLabel *price,int num);
    void plusClick(QLineEdit* quant, QLabel *price,int num);
    void minusClick(QLineEdit* quant, QLabel *price,int num);
    void back_submit_click(int num);
};

#endif // PRODUCTINFO_H
