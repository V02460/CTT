#include "FileVideoTest.h"
#include "CustomTestingMacros.h"
#include "..\CTT\YUVDataVideo.h"
#include "qoffscreensurface.h"

void FileVideoTest::initTestCase()
{
	surface.create();
	testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
	testContext->create();
	QVERIFY2(testContext->makeCurrent(&surface), "Couldn't initialize OGL Context.");
}

void FileVideoTest::test()
{
	model::video::YUVDataVideo::sptr testVideo(new model::video::YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
	QVERIFY(testVideo->getContext() == testContext);
	QCOMPARE(testVideo->getPath(), QString("Resources/Videos/YUV444/squirrel-720x576-444P.yuv"));
	QVERIFY(testVideo->uses(*testVideo.data()));
	QCOMPARE(testVideo->getUsesList().size(), 1);
	QVERIFY(testVideo->getUsesList().at(0) == testVideo);
}
