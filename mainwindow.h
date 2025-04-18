#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include "inventory.h"
#include "productinfo.h"
#include <QRadioButton>
#include <QButtonGroup>
#include "cartviewwindow.h"
#include "user.h"



class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(User &user,QWidget *parent = nullptr);
private:
    Inventory inventory;
    vector<QPushButton*> items;
    vector<QPushButton*> items1;
    ProductInfo *productinfo;
    Cart cart;
    QLineEdit *search_bar;
    vector<QPushButton*> searchedItems;
    QPushButton *clear;
    QRadioButton *lowToHigh;
    QRadioButton *highToLow;
    QButtonGroup *group;
    QButtonGroup *categories;
    QCheckBox *clothes;
    QCheckBox *electronics;
    QCheckBox *furniture;
    QPushButton *viewCartButton;
    CartViewWindow *cartviewing;
    User user;
private slots:
    void productClick(std::string name);
    void searching(QWidget *container);
    void clearing(QWidget *container);
    void filteringPrice(QAbstractButton* button, QWidget *container, std::vector<Product *> products);
    void populateInventory(Inventory &inv);
    void filteringCategory(int state,std::string category, QWidget *container);
    void viewingCart();
    void clearButtons();
};

#endif // MAINWINDOW_H
