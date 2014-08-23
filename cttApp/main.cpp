#include <QApplication>
#include "ctt.h"

#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QMessageBox>

#include "MockDisplayHelper.h"
#include "YUVDataVideo.h"
#include "FFmpegDataVideo.h"
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

		model::video::YUVDataVideo testVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext);

		//model::video::FFmpegDataVideo testVideo("Resources/Videos/mp4/mp4test.mp4", testContext);

		testVideo.save("Resources/Videos/YUV444/XXXSAVEDVIDEOsquirrel-720x576-444P.yuv", model::video::VideoFileType::YUV);
		MockDisplayHelper::showImage(testVideo.getFrame(10)->getFramebufferObject()->toImage());
		       
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