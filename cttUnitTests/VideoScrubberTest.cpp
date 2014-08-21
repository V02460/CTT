#include "VideoScrubberTest.h"
#include "..\ctt\VideoScrubber.h"
#include "..\ctt\IllegalStateException.h"
#include "CustomTestingMacros.h"
#include "..\CTT\YUVDataVideo.h"
#include "qoffscreensurface.h"

using model::player::VideoScrubber;
using exception::IllegalArgumentException;
using model::video::YUVDataVideo;

void VideoScrubberTest::testDummy()
{
 	QSharedPointer<model::saveable::Saveable> dummy = VideoScrubber::getDummy();

 	QVERIFY2(dummy->isDummy(), "The generated dummy claimed not to be a dummy.");
}


void VideoScrubberTest::methods()
{
	model::video::YUVDataVideo *testVideo = new model::video::YUVDataVideo("C:/Users/Jonas/Source/Repos/CTT/x64/Debug/testresources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext);
	YUVDataVideo::sptr videoPointer(testVideo);
	VideoScrubber testScrubber(videoPointer);

	QVERIFY(testScrubber.getVideoMetadata().getSize() == testVideo->getMetadata().getSize());

	QCOMPARE(testScrubber.getFrameCount(), testVideo->getFrameCount());

	QVERIFY(testScrubber.getVideo() == videoPointer);

	QVERIFY(!testScrubber.isWaitingForFrame());

	testScrubber.getCurrentFrame();
	testScrubber.jumpToFrameNr(10);
	testScrubber.getCurrentFrame();

	QEXPECT_EXCEPTION(testScrubber.jumpToFrameNr(testScrubber.getFrameCount()), IllegalArgumentException);
	
	VideoScrubber testScrubber2(videoPointer, 10);

	QEXPECT_EXCEPTION(VideoScrubber testScrubber3(videoPointer, 20), IllegalArgumentException);
}

void VideoScrubberTest::initTestCase()
{
	surface.create();

	testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
	testContext->create();
	QVERIFY2(testContext->makeCurrent(&surface), "Couldn't initialize OGL Context.");
}
