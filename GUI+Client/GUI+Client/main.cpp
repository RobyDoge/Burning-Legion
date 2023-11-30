#include "loginWindow.h"
#include <QtWidgets/QApplication>
#include <qwidget.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow* loginWindow = new LoginWindow();
    loginWindow->show();
    return a.exec();
}
