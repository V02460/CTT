#include <QApplication>
#include "ctt.h"

#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QMessageBox>
#include <QTranslator>
#include <QLibraryInfo>

#include "MockDisplayHelper.h"
#include "YUVDataVideo.h"
#include "FFmpegDataVideo.h"
#include "Frame.h"
#include "BlueHistogram.h"
#include "Surface.h"
#include "RuntimeException.h"
#include "VideoWidget.h"
#include "ThumbnailListWidgetTest.h"
#include "ListedPushButtonTest.h"
#include "ProcessingWidget.h"
#include "Project.h"
#include "YUVDataVideo.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "VideoScrubber.h"
#include "MainWindow.h"
#include "GPUSurfaceShader.h"
#include "YUVType.h"

using ::helper::MockDisplayHelper;
using ::model::frame::Frame;
using ::model::frame::histogram::BlueHistogram;
using ::model::Surface;
using ::helper::GPUSurfaceShader;
using ::exception::RuntimeException;
using ::controller::project::Project;
using ::controller::VideoListController;
using ::model::video::Video;
using ::model::saveable::SaveableList;
using ::model::video::YUVDataVideo;
using ::model::filter::FilteredVideo;
using ::model::player::Player;
using ::model::player::VideoScrubber;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //ctt mainWindow;
	//view::VideoWidget *videoWidget;
	//ThumbnailListWidgetTest *thumbnailListWidgetTest;
	//ListedPushButtonTest *listedPushButtonTest;
	//view::ProcessingWidget *processingWidget;
	view::MainWindow *mainWindow;

	a.setWindowIcon(QIcon("Resources/Icons/Logo.png"));

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator cttTranslator;
    cttTranslator.load("ctt_" + QLocale::system().name());
    a.installTranslator(&cttTranslator);

	//TODO wieder einkommentieren
    //try {
        //mainWindow.show();

        /*QOffscreenSurface surface;
        surface.create();

        QSharedPointer<QOpenGLContext> testContext(new QOpenGLContext());
        testContext->create();
        if (!testContext->makeCurrent(&surface)) {
            return 1;
        }

        QImage image(":/cttApp/SmallBuckBunny.png");
        if (image.isNull()) {
            return 1;
        }*

        //Frame::sptr frame(new Frame(testContext, image));
        //BlueHistogram histogram(*frame.data());

        /*Surface::sptr histogramImage = histogram.getHistogramImage();
        MockDisplayHelper::showImage(histogramImage->getFramebufferObject()->toImage());*/

		//videoWidget = new view::VideoWidget(frame);
		//videoWidget->show();

		//listedPushButtonTest = new ListedPushButtonTest();
		//listedPushButtonTest->show();

		//thumbnailListWidgetTest = new ThumbnailListWidgetTest();
		//thumbnailListWidgetTest->show();

		Project *testProject = Project::getInstance();
		/*VideoListController::sptr analysingVideosController =
			VideoListController::sptr(new VideoListController(testProject->getVideoList2().dynamicCast<SaveableList<Video>>()));

		YUVDataVideo::sptr testVideoOne = YUVDataVideo::sptr(new YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
		VideoScrubber::sptr testVideoScrubberOne = VideoScrubber::sptr(new VideoScrubber(testVideoOne));
		testProject->getBaseVideoList()->insert(0, testVideoOne);

		FilteredVideo::sptr testFilteredVideoOne = FilteredVideo::sptr(new FilteredVideo(testVideoOne));
		VideoScrubber::sptr testFilteredVideoScrubberOne = VideoScrubber::sptr(new VideoScrubber(testFilteredVideoOne));
		testProject->getVideoList1()->insert(0, testFilteredVideoOne);

		Player::sptr testPlayerOne = Player::sptr(new Player(24));
		testPlayerOne->addScrubber(testVideoScrubberOne);
		testPlayerOne->addScrubber(testFilteredVideoScrubberOne);
		testProject->getPlayerList1()->insert(0, testPlayerOne);


		YUVDataVideo::sptr testVideoTwo = YUVDataVideo::sptr(new YUVDataVideo("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext));
		VideoScrubber::sptr testVideoScrubberTwo = VideoScrubber::sptr(new VideoScrubber(testVideoTwo));
		testProject->getBaseVideoList()->insert(1, testVideoTwo);

		FilteredVideo::sptr testFilteredVideoTwo = FilteredVideo::sptr(new FilteredVideo(testVideoTwo));
		VideoScrubber::sptr testFilteredVideoScrubberTwo = VideoScrubber::sptr(new VideoScrubber(testFilteredVideoTwo));
		testProject->getVideoList1()->insert(1, testFilteredVideoTwo);

		Player::sptr testPlayerTwo = Player::sptr(new Player(24));
		testPlayerTwo->addScrubber(testVideoScrubberTwo);
		testPlayerTwo->addScrubber(testFilteredVideoScrubberTwo);
		testProject->getPlayerList1()->insert(1, testPlayerTwo);*/


		//(processingWidget = new view::ProcessingWidget(testProject->getPlayerList1(), testProject->getVideoList1(),
		//	testProject->getBaseVideoList(), analysingVideosController);
		//processingWidget->show();

		mainWindow = new view::MainWindow();
		mainWindow->show();
    /*}

    catch (RuntimeException *e) {
//         QMessageBox msgBox;
//         msgBox.setWindowTitle(e->getName());
//         msgBox.setText(e->getMsg());
//         msgBox.exec();
        qDebug() << e->getName() << e->getMsg();
    }*/

    return a.exec();
}