#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LoginWindow login;
    login.showMaximized();
    return app.exec();
}
