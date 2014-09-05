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
#include "..\ctt\GlobalContext.h"

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
	ctt mainWindow;
	try {
		mainWindow.show();

		//model::video::YUVDataVideo testVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, model::GlobalContext::get());
		model::video::FFmpegDataVideo testVideo("resources/Videos/mp4/Wildes Holz(720p_H.264-AAC).mp4", model::GlobalContext::get());

		qDebug() << (QString::number(testVideo.getMetadata().getSize().width()) + "*" + QString::number(testVideo.getMetadata().getSize().height()));
		qDebug() << QString::number(testVideo.getMetadata().getFPS());
		qDebug() << testVideo.getMetadata().getLength();

		MockDisplayHelper::showImage(testVideo.getFrame(10)->getFramebufferObject()->toImage());
	}
	catch (RuntimeException *e) {
		qDebug() << e->getName() << e->getMsg();
	}
	return a.exec();
}