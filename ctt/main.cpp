#include "ctt.h"
#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	::view::MainWindow *mw = new ::view::MainWindow();
    mw->show();
    return a.exec();
}
