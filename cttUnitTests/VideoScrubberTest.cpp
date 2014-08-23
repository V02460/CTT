#include "VideoScrubberTest.h"

#include "VideoScrubber.h"
#include "CustomTestingMacros.h"
#include "YUVDataVideo.h"

#include "IllegalStateException.h"

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
	model::video::YUVDataVideo *testVideo = new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext);
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

void VideoScrubberTest::saveRestore()
{
	model::video::YUVDataVideo *testVideo = new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext);
	YUVDataVideo::sptr videoPointer(testVideo);
	VideoScrubber testScrubber(videoPointer);

	model::saveable::Memento memento = testScrubber.getMemento();

	VideoScrubber::sptr dummy = VideoScrubber::getDummy().dynamicCast<VideoScrubber>();

	dummy->restore(memento);
	QVERIFY(!dummy->isDummy());
	QVERIFY(dummy->getVideo() == videoPointer);


	model::video::YUVDataVideo *testVideo2 = new model::video::YUVDataVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, testContext);
	YUVDataVideo::sptr videoPointer2(testVideo2);
	VideoScrubber testScrubber2(videoPointer2);

	testScrubber2.restore(memento);
	QVERIFY(testScrubber2.getVideo() == videoPointer);

	YUVDataVideo::sptr nullPointer;
	memento.setSharedPointer("video", nullPointer);
	QEXPECT_EXCEPTION(dummy->restore(memento), IllegalArgumentException);
}
