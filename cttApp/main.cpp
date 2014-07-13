#include <QApplication>
#include "ctt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ctt mainWindow;

    mainWindow.show();

    return a.exec();
}