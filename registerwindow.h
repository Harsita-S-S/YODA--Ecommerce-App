#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QMessageBox>
class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private:

    QLabel *addressHeader;
    QLabel *fullName;
    QLabel *streetAddress;
    QLabel *password;
    QLabel *email;
    QLabel *phoneNumber;

    QLineEdit *fullNameEdit;
    QLineEdit *streetAddressEdit;
    QLineEdit *passwordEdit;
    QLineEdit *emailEdit;
    QLineEdit *phoneNumberEdit;
    QPushButton *ok;

    QDialogButtonBox *buttonBox;

    QVBoxLayout *formLayout;
    QVBoxLayout *mainLayout;
private slots:
    void saveDetails();
    void cancelDetails();
};

#endif
