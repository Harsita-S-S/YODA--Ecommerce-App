#ifndef ONLINEPAYMENTWINDOW_H
#define ONLINEPAYMENTWINDOW_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class OnlinePaymentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OnlinePaymentWindow(int count, QWidget *parent = nullptr);

private slots:
    void handlePayment(int count);

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *payButton;
};

#endif
