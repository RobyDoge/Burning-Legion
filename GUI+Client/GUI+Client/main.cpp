#include "GUIClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUIClient w;
    w.show();
    return a.exec();
}
