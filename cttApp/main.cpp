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
#include "GPUHelper.h"
#include "VideoWidget.h"

using ::helper::MockDisplayHelper;
using ::model::frame::Frame;
using ::model::frame::histogram::BlueHistogram;
using ::model::Surface;
using ::helper::GPUHelper;
using ::exception::RuntimeException;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ctt mainWindow;
	view::VideoWidget *videoWidget;

    try {
        //mainWindow.show();

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

        Frame::sptr frame(new Frame(testContext, image));
        BlueHistogram histogram(*frame.data());

        Surface::sptr histogramImage = histogram.getHistogramImage();
        //MockDisplayHelper::showImage(histogramImage->getFramebufferObject()->toImage());

		videoWidget = new view::VideoWidget(frame.data());
		videoWidget->show();
    }
    catch (RuntimeException *e) {
//         QMessageBox msgBox;
//         msgBox.setWindowTitle(e->getName());
//         msgBox.setText(e->getMsg());
//         msgBox.exec();
        qDebug() << e->getName() << e->getMsg();
    }

    return a.exec();
}