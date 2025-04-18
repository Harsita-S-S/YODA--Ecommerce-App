#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include "mainwindow.h"
#include "registerwindow.h"
#include "user.h"
#include <fstream>

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void handleLogin();
    void openRegisterWindow();

private:
    User user;
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *loginButton;
    QPushButton *registerButton;

    MainWindow *mainwindow;
    RegisterWindow *registerWindow;
};

#endif
