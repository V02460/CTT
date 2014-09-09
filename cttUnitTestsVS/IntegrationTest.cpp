#include <CppUnitTest.h>

#include <QApplication>
#include <QOpenGLContext>
#include <QDir>

#include "GreyscaleFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"
#include "YUVDataVideo.h"
#include "MainWindow.h"

#include "AccessToDummyException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ctt_unit_tests {

using ::model::filter::GreyscaleFilter;
using ::model::video::YUVDataVideo;
using ::model::filter::FilterParam;
using ::model::GlobalContext;
using ::model::video::YUVType;
using ::model::saveable::Memento;
using ::exception::AccessToDummyException;

QApplication *a;

TEST_MODULE_INITIALIZE(init) {
    char *argv[] = {""};
    int argc = 1;
    a = new QApplication(argc, argv);   
}

TEST_MODULE_CLEANUP(ModuleClean) {
    delete a;
}

TEST_CLASS(IntegrationTest) {
public:
    TEST_METHOD(testRun) {
        view::MainWindow *mainWindow = new view::MainWindow();
        mainWindow->show();

        a->exec();
    }
};

}