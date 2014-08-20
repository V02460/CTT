#include <QApplication>
#include "ctt.h"

#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QMessageBox>

#include "MockDisplayHelper.h"
#include "YUVDataVideo.h"
#include "Frame.h"
#include "BlueHistogram.h"
#include "Surface.h"
#include "RuntimeException.h"
#include "GPUHelper.h"
#include "..\CTT\YUVType.h"
#include <stdlib.h>

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

    try {
        mainWindow.show();

        QOffscreenSurface surface;
        surface.create();

        QSharedPointer<QOpenGLContext> testContext(new QOpenGLContext());
        testContext->create();
        if (!testContext->makeCurrent(&surface)) {
            return 1;
        }

//         QImage image(":/cttApp/SmallBuckBunny.png");
//         if (image.isNull()) {
//             return 1;
//         }
// 
//         Frame::sptr frame(new Frame(testContext, image));
//         BlueHistogram histogram(*frame.data());
// 
//         Surface::sptr histogramImage = histogram.getHistogramImage();

		model::video::YUVDataVideo testVideo("C:/Users/Jonas/Source/Repos/CTT/x64/Debug/testresources/Videos/YUV420CIF/stefan_cif.yuv", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);


		MockDisplayHelper::showImage(testVideo.getFrame(50)->getFramebufferObject()->toImage());
		       
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