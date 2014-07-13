#include <QApplication>
#include "ctt.h"

#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QMessageBox>

#include "MockDisplayHelper.h"
#include "Frame.h"
#include "BlueHistogram.h"
#include "Surface.h"
#include "RuntimeException.h"

using ::helper::MockDisplayHelper;
using ::model::frame::Frame;
using ::model::frame::histogram::BlueHistogram;
using ::model::Surface;
using ::exception::RuntimeException;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ctt mainWindow;

    try {
        mainWindow.show();

        QOffscreenSurface surface;
        surface.create();

        QSharedPointer<QOpenGLContext> testContext(new QOpenGLContext());
        testContext->create();
        if (!testContext->makeCurrent(&surface)) {
            return 1;
        }

        QImage image(":/cttApp/SmallBuckBunny.png");
        if (image.isNull()) {
            return 1;
        }

        Frame frame(testContext, image);
        BlueHistogram histogram(frame);

        Surface::sptr grid = histogram.makeHistogramGrid(frame);
    
        glFlush();

        MockDisplayHelper::showImage(grid->getFramebufferObject()->toImage());
    }
    catch (RuntimeException *e) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(e->getName());
        msgBox.setText(e->getMsg());
        msgBox.exec();
    }

    return a.exec();
}