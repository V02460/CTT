#include "ctt.h"
#include <QtWidgets/QApplication>
#include "MainWindow.h"

#include "TestResult.h"

#include "ModelTests.h"
//#include "ViewTests.h"
//#include "ControllerTests.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    TestResult r("");

    r << model::test(argc, argv);

    r.print("");
	::view::MainWindow *mw = new ::view::MainWindow();
    mw->show();
    return a.exec();
}
