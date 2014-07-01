#include "ctt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ctt w;
    w.show();
    return a.exec();
}
