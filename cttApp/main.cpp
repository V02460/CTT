#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 	view::MainWindow *mainWindow;

    a.setWindowIcon(QIcon("Resources/Icons/Logo.png"));

    // Qt translations
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    // CTT translations
    QTranslator cttTranslator;
    //cttTranslator.load("ctt_" + QLocale::system().name());
    if (argc >= 2 && QString(argv[1]) == "en") {
        cttTranslator.load("ctt_en");
    } else {
        cttTranslator.load("ctt_de");
    }
    
    a.installTranslator(&cttTranslator);

    // Open the main window
	mainWindow = new view::MainWindow();
	mainWindow->show();

    // Start event loop
    return a.exec();
}