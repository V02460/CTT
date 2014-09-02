#include "VideoScrubberTest.h"

#include "VideoScrubber.h"
#include "CustomTestingMacros.h"
#include "YUVDataVideo.h"
#include "GlobalContext.h"

#include "IllegalStateException.h"

using model::player::VideoScrubber;
using model::video::YUVDataVideo;
using model::GlobalContext;
using model::saveable::Saveable;
using model::video::YUVDataVideo;
using exception::IllegalArgumentException;

void VideoScrubberTest::testDummy() {
 	Saveable::sptr dummy = VideoScrubber::getDummy();

 	QVERIFY2(dummy->isDummy(), "The generated dummy claimed not to be a dummy.");
}


void VideoScrubberTest::methods() {
    YUVDataVideo::sptr testVideo(new YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
	VideoScrubber testScrubber(testVideo);

	QVERIFY(testScrubber.getVideoMetadata().getSize() == testVideo->getMetadata().getSize());

	QCOMPARE(testScrubber.getFrameCount(), testVideo->getFrameCount());

	QVERIFY(testScrubber.getVideo() == testVideo);

	QVERIFY(!testScrubber.isWaitingForFrame());

	testScrubber.getCurrentFrame();
	testScrubber.jumpToFrameNr(10);
	testScrubber.getCurrentFrame();

	QEXPECT_EXCEPTION(testScrubber.jumpToFrameNr(testScrubber.getFrameCount()), IllegalArgumentException);
	
	VideoScrubber testScrubber2(testVideo, 10);

	QEXPECT_EXCEPTION(VideoScrubber testScrubber3(testVideo, 20), IllegalArgumentException);
}

void VideoScrubberTest::initTestCase() {
	testContext = GlobalContext::get();
}

void VideoScrubberTest::saveRestore() {
    YUVDataVideo::sptr testVideo(new YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
    VideoScrubber testScrubber(testVideo);

	Memento memento = testScrubber.getMemento();

	VideoScrubber::sptr dummy = VideoScrubber::getDummy().dynamicCast<VideoScrubber>();

	dummy->restore(memento);
	QVERIFY(!dummy->isDummy());
    QVERIFY(dummy->getVideo() == testVideo);


    YUVDataVideo::sptr testVideo2(new YUVDataVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, testContext));
    VideoScrubber testScrubber2(testVideo2);

	testScrubber2.restore(memento);
    QVERIFY(testScrubber2.getVideo() == testVideo);

	YUVDataVideo::sptr nullPointer;
	memento.setSharedPointer("video", nullPointer);
	QEXPECT_EXCEPTION(dummy->restore(memento), IllegalArgumentException);
}
