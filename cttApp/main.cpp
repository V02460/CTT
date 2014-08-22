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
#include "VideoWidget.h"
#include "ThumbnailListWidgetTest.h"
#include "ListedPushButtonTest.h"
#include "ProcessingWidget.h"
#include "Project.h"

using ::helper::MockDisplayHelper;
using ::model::frame::Frame;
using ::model::frame::histogram::BlueHistogram;
using ::model::Surface;
using ::helper::GPUHelper;
using ::exception::RuntimeException;
using ::controller::project::Project;
using ::controller::VideoListController;
using ::model::video::Video;
using ::model::saveable::SaveableList;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //ctt mainWindow;
	view::VideoWidget *videoWidget;
	ThumbnailListWidgetTest *thumbnailListWidgetTest;
	ListedPushButtonTest *listedPushButtonTest;
	view::ProcessingWidget *processingWidget;

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

        /*Surface::sptr histogramImage = histogram.getHistogramImage();
        MockDisplayHelper::showImage(histogramImage->getFramebufferObject()->toImage());*/

		videoWidget = new view::VideoWidget(frame);
		videoWidget->show();

		listedPushButtonTest = new ListedPushButtonTest();
		listedPushButtonTest->show();

		thumbnailListWidgetTest = new ThumbnailListWidgetTest();
		thumbnailListWidgetTest->show();

		Project *testProject = Project::getInstance();
		VideoListController::sptr analysingVideosController =
			VideoListController::sptr(new VideoListController(testProject->getVideoList2().dynamicCast<SaveableList<Video>>()));
		processingWidget = new view::ProcessingWidget(testProject->getPlayerList1(), testProject->getVideoList1(),
			testProject->getBaseVideoList(), analysingVideosController);
		processingWidget->show();
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