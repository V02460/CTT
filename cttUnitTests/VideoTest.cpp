#include "VideoTest.h"
#include "CustomTestingMacros.h"
#include "..\CTT\YUVDataVideo.h"
#include "qoffscreensurface.h"

void VideoTest::initTestCase()
{
	surface.create();
	testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
	testContext->create();
	QVERIFY2(testContext->makeCurrent(&surface), "Couldn't initialize OGL Context.");
}

void VideoTest::test()
{
	model::video::YUVDataVideo::sptr testVideo(new model::video::YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
	QVERIFY(testVideo->getResolution() == testVideo->getMetadata().getSize());
	//TODO igzgf scaledFrame und save
}
