#include "checkoutwindow.h"
#include "deliveryandpayment.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QFont>
#include <QScreen>
#include <QGuiApplication>
#include "cart.h"

CheckoutWindow::CheckoutWindow(Cart *cart, QWidget *parent)
    : QDialog(parent),cart(cart)
{
    this->setGeometry(QGuiApplication::primaryScreen()->availableGeometry());
    this->setMinimumSize(800, 600);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *contentLayout = new QVBoxLayout();

    QLabel *headingLabel = new QLabel("Checkout", this);
    headingLabel->setAlignment(Qt::AlignCenter);
    QFont headingFont;
    headingFont.setPointSize(24);
    headingFont.setBold(true);
    headingLabel->setFont(headingFont);
    headingLabel->setStyleSheet("margin-top: 20px; margin-bottom: 15px;");
    contentLayout->addWidget(headingLabel);


    tableWidget = new QTableWidget(this);
    tableWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    tableWidget->setMinimumSize(700, 300);
    contentLayout->addWidget(tableWidget, 0, Qt::AlignHCenter);

    labelTotal = new QLabel("Total amount", this);
    QFont headerFont;
    headerFont.setPointSize(16);
    headerFont.setBold(true);
    labelTotal->setFont(headerFont);
    labelTotal->setAlignment(Qt::AlignCenter);
    contentLayout->addWidget(labelTotal);

    buttonProceed = new QPushButton("Next", this);
    buttonProceed->setFixedHeight(60);
    buttonProceed->setMinimumWidth(150);
    buttonProceed->setStyleSheet("font-size: 16px; padding: 8px 20px; margin: 10px 20px; "
                                 "background-color: #4CAF50; color: white; border: none; border-radius: 5px;");
    contentLayout->addWidget(buttonProceed, 0, Qt::AlignCenter);

    mainLayout->addLayout(contentLayout);


    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    mainLayout->addWidget(buttonBox);

    populateTable(cart->getCartItems(),cart->getQuantities());

    connect(buttonProceed, &QPushButton::clicked, this, &CheckoutWindow::onProceedClicked);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CheckoutWindow::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CheckoutWindow::reject);
}


CheckoutWindow::~CheckoutWindow(){}

void CheckoutWindow::populateTable(const std::vector<Product> &cartItems,const std::vector<int> &quantities)
{
    tableWidget->setColumnCount(5);
    tableWidget->setHorizontalHeaderLabels({"Product", "Category", "Quantity", "Price ($)", "Subtotal ($)"});
    tableWidget->setRowCount(static_cast<int>(cartItems.size()));
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    double total=0.0;

    for (int row=0;row<cartItems.size();row++)
    {
        const Product &p = cartItems[row];
        int quantity=0;
        if(row < quantities.size())
        {
            quantity=quantities[row];
        }
        else
        {
            quantity=0;
        }
        double subtotal = p.getPrice()*quantity;
        total += subtotal;
        tableWidget->setItem(row,0,new QTableWidgetItem(QString::fromStdString(p.getName())));
        tableWidget->setItem(row,1,new QTableWidgetItem(QString::fromStdString(p.getCategory())));
        tableWidget->setItem(row,2,new QTableWidgetItem(QString::number(quantity)));
        tableWidget->setItem(row,3,new QTableWidgetItem(QString::number(p.getPrice(),'f',2)));
        tableWidget->setItem(row,4,new QTableWidgetItem(QString::number(subtotal,'f',2)));

        for (int col = 0; col < 5; ++col)
        {
            tableWidget->item(row, col)->setTextAlignment(Qt::AlignCenter);
        }
    }

    labelTotal->setText("Total: $" + QString::number(total, 'f', 2));
}

void CheckoutWindow::onProceedClicked()
{
    this->accept();
    qDebug()<<cart;
    DeliveryAndPayment* addressWindow = new DeliveryAndPayment(cart);
    addressWindow->resize(700, 500);
    addressWindow->exec();
}
