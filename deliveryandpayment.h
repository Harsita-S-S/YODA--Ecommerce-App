#ifndef DELIVERYANDPAYMENT_H
#define DELIVERYANDPAYMENT_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include "cart.h"

namespace Ui
{
class DeliveryAndPayment;
}

class DeliveryAndPayment : public QDialog
{
    Q_OBJECT

public:
    ~DeliveryAndPayment() ;
    explicit DeliveryAndPayment(Cart *cart, QWidget *parent = nullptr);
    QString getFullName() const;
    QString getStreetAddress() const;

    QString getPhoneNumber() const;
    bool isSaveAddressChecked() const;

private slots:
    void confirmPayment();

private:
    Cart *cart;

    QLineEdit *fullNameEdit;
    QLineEdit *streetAddressEdit;
    int count;
    QLineEdit *phoneNumberEdit;
    QCheckBox *saveAddressCheckBox;
    QDialogButtonBox *buttonBox;
    QWidget *orderSummaryWidget;
    QTextEdit *orderSummaryEdit;
    QLabel *orderSummaryLabel;
    QWidget *paymentMethodWidget;
    QComboBox *paymentComboBox;
    QLabel *paymentMethodLabel;
    QPushButton *confirmButton;
    QScrollArea *scrollArea;
};

#endif
