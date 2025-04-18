#include "widget.h"
#include "mainwindow.h"
#include "registerwindow.h"


LoginWindow::LoginWindow(QWidget *parent): QWidget(parent) {

    QLabel *welcome = new QLabel("WELCOME TO YODA",this);
    welcome->setGeometry(425,80,400,40);

    QLabel *Login = new QLabel("Login",this);
    Login->setGeometry(560,200,100,40);

    QFont normal;
    normal.setPointSize(30);
    welcome->setFont(normal);
    normal.setPointSize(20);
    Login->setFont(normal);
    QLabel *usernameLabel = new QLabel("Username:", this);
    usernameInput = new QLineEdit(this);
    usernameInput->setFixedSize(150, 30);

    QLabel *passwordLabel = new QLabel("Password:", this);
    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setFixedSize(150, 30);

    loginButton = new QPushButton("Login", this);
    loginButton->setFixedSize(100, 40);

    registerButton = new QPushButton("Register", this);
    registerButton->setFixedSize(100, 40);

    QWidget *formContainer = new QWidget(this);
    QGridLayout *layout = new QGridLayout(formContainer);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 2);
    layout->setColumnStretch(3, 1);
    layout->setColumnStretch(4, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(5, 1);

    layout->addWidget(usernameLabel, 1, 1);
    layout->addWidget(usernameInput, 1, 2);
    layout->addWidget(passwordLabel, 2, 1);
    layout->addWidget(passwordInput, 2, 2);
    layout->addWidget(loginButton, 3, 2);
    layout->addWidget(registerButton, 4, 2);

    formContainer->setLayout(layout);
    formContainer->setStyleSheet("border: 2px solid white; padding: 1px; border-radius: 5px;");
    formContainer->setGeometry(450, 250, 300, 250);

    setWindowTitle("Login");

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::openRegisterWindow);
}

void LoginWindow::handleLogin() {
    QString username = usernameInput->text();
    QString password = passwordInput->text();
    ifstream f1;
    int flag=0;
    int count=0;
    f1.open(R"(C:\Users\kalal\OneDrive\Documents\LoginPage\UserDetails.txt)");
    while(f1)
    {
        string data;
        getline(f1,data);
        QString user = QString::fromStdString(data);
        QStringList details = user.split(",");
        count++;
        if(details[0]==username && details[1]==password)
        {

            User user;
            user.setName(username.toStdString());
            user.setPassword(password.toStdString());
            mainwindow = new MainWindow(user);
            mainwindow->showMaximized();
            this->close();
            flag=1;
            break;
        }

    }
    if(flag==0)
    {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
    f1.close();
    ofstream fh;
    fh.open(R"(C:\Users\kalal\OneDrive\Documents\LoginPage\UserDetails.txt)", ios::app);
    fh.seekp(0, ios::end);
    fh << count;
    fh.close();
}

void LoginWindow::openRegisterWindow() {
    if(registerWindow)
    {
        registerWindow=nullptr;
    }
    registerWindow = new RegisterWindow();
    registerWindow->show();
}
