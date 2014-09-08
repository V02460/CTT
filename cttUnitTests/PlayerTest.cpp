#include "PlayerTest.h"

#include "YUVDataVideo.h"
#include "VideoScrubber.h"
#include "CustomTestingMacros.h"
#include "UIntegerInterval.h"
#include "GlobalContext.h"
#include "Memento.h"

#include "IllegalArgumentException.h"

namespace model {
namespace player {

using ::model::video::YUVDataVideo;
using ::model::GlobalContext;
using ::exception::IllegalArgumentException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::model::video::YUVType;

void PlayerTest::emptyPlayer() {
	Player test(10);

	QVERIFY(!test.isPlaying());
	QVERIFY(!test.isLooping());

	QVERIFY(test.getScrubbers().isEmpty());

	QVERIFY(!test.hasNextFrame());
	QVERIFY(!test.hasPreviousFrame());

	QCOMPARE(test.scrubberCount(), 0U);
	QCOMPARE(test.getVideoLength(), 0U);
	QCOMPARE(test.getCurrentFrameNumber(), 0U);

	QCOMPARE(test.getFPS(), 10.0);

	test.setFPS(20);
	QCOMPARE(test.getFPS(), 20.0);
}

void PlayerTest::playingAndLooping() {
	YUVDataVideo *testVideo = new YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, YUVType::YUV444, testContext);
	YUVDataVideo::sptr videoPointer(testVideo);
	VideoScrubber::sptr testScrubber(new VideoScrubber(videoPointer));

	Player testPlayer(10);
	testPlayer.addScrubber(testScrubber);

	QVERIFY(!testPlayer.isPlaying());
	QVERIFY(!testPlayer.hasPreviousFrame());
	QVERIFY(testPlayer.hasNextFrame());
	QCOMPARE(testPlayer.getCurrentFrameNumber(), 0U);

	testPlayer.previousFrame();
	QVERIFY(!testPlayer.hasPreviousFrame());
	QVERIFY(testPlayer.hasNextFrame());
	QCOMPARE(testPlayer.getCurrentFrameNumber(), 0U);

	testPlayer.nextFrame();
	QVERIFY(testPlayer.hasPreviousFrame());
	QVERIFY(testPlayer.hasNextFrame());
	QCOMPARE(testPlayer.getCurrentFrameNumber(), 1U);


	testPlayer.jumpToFrameNr(13);
	QVERIFY(testPlayer.hasPreviousFrame());
	QVERIFY(testPlayer.hasNextFrame());
	QCOMPARE(testPlayer.getCurrentFrameNumber(), 13U);

	testPlayer.nextFrame();
	QVERIFY(testPlayer.hasPreviousFrame());
	QVERIFY(!testPlayer.hasNextFrame());
	QCOMPARE(testPlayer.getCurrentFrameNumber(), 14U);

	QEXPECT_EXCEPTION(testPlayer.jumpToFrameNr(100), IllegalArgumentException);

	testPlayer.play();
	QVERIFY(testPlayer.isPlaying());
	testPlayer.pause();
	QVERIFY(!testPlayer.isPlaying());
	testPlayer.togglePlayPause();
	QVERIFY(testPlayer.isPlaying());
	testPlayer.togglePlayPause();
	QVERIFY(!testPlayer.isPlaying());

	testPlayer.play();
	testPlayer.nextFrame();
	QVERIFY(!testPlayer.isPlaying());

    testPlayer.play();
    testPlayer.previousFrame();
    QVERIFY(!testPlayer.isPlaying());

	UIntegerInterval testInterval(5, 10);
	QVERIFY(!testPlayer.isLooping());
	testPlayer.setLoop(testInterval);
	QVERIFY(testPlayer.isLooping());
	QCOMPARE(testPlayer.getLoop().getStart(), 5U);
	QCOMPARE(testPlayer.getLoop().getEnd(), 10U);
	testPlayer.jumpToFrameNr(10);
	QCOMPARE(testPlayer.getCurrentFrameNumber(), 10U);
	testPlayer.nextFrame();
	QCOMPARE(testPlayer.getCurrentFrameNumber(), 5U);
	testPlayer.nextFrame();
	QCOMPARE(testPlayer.getCurrentFrameNumber(), 6U);
	testPlayer.previousFrame();
	testPlayer.previousFrame();
	QCOMPARE(testPlayer.getCurrentFrameNumber(), 10U);

	testPlayer.stopLooping();
	QVERIFY(!testPlayer.isLooping());
	testPlayer.nextFrame();
	QCOMPARE(testPlayer.getCurrentFrameNumber(), 11U);

	UIntegerInterval testInterval2(0, 14);
	testPlayer.setLoop(testInterval2);

	UIntegerInterval testInterval3(0, 100);
	QEXPECT_EXCEPTION(testPlayer.setLoop(testInterval3), IllegalArgumentException);
}

void PlayerTest::scrubberOperations()
{
	YUVDataVideo *testVideo = new YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, YUVType::YUV444, testContext);
	YUVDataVideo::sptr videoPointer(testVideo);
	VideoScrubber::sptr testScrubber(new VideoScrubber(videoPointer));

	YUVDataVideo *testVideo2 = new YUVDataVideo("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, YUVType::YUV420, testContext);
	YUVDataVideo::sptr videoPointer2(testVideo2);
	VideoScrubber::sptr testScrubber2(new VideoScrubber(videoPointer2));

	Player testPlayer(10);

	QVERIFY(testPlayer.getScrubbers().isEmpty());

	testPlayer.addScrubber(testScrubber2);
	QCOMPARE(testPlayer.scrubberCount(), 1U);
	QCOMPARE(testPlayer.getVideoLength(), videoPointer2->getFrameCount());
	QVERIFY(testPlayer.getScrubbers().contains(testScrubber2));
	QVERIFY(testPlayer.controlsScrubber(*testScrubber2));

	testPlayer.addScrubber(testScrubber);
	QCOMPARE(testPlayer.scrubberCount(), 2U);
	QCOMPARE(testPlayer.getVideoLength(), videoPointer->getFrameCount());
	QVERIFY(testPlayer.getScrubbers().contains(testScrubber));
	QVERIFY(testPlayer.controlsScrubber(*testScrubber));

	testPlayer.removeScrubber(*testScrubber);
	QCOMPARE(testPlayer.scrubberCount(), 1U);
	QCOMPARE(testPlayer.getVideoLength(), videoPointer2->getFrameCount());
	QVERIFY(!testPlayer.getScrubbers().contains(testScrubber));
	QVERIFY(!testPlayer.controlsScrubber(*testScrubber));

	testPlayer.addScrubber(testScrubber, 0U);
	QCOMPARE(testPlayer.scrubberCount(), 2U);
	QCOMPARE(testPlayer.getVideoLength(), videoPointer->getFrameCount());
	QVERIFY(testPlayer.getScrubbers().at(0) == testScrubber);
	QVERIFY(testPlayer.controlsScrubber(*testScrubber));

	testPlayer.removeScrubber(0);
	QCOMPARE(testPlayer.scrubberCount(), 1U);
	QCOMPARE(testPlayer.getVideoLength(), videoPointer2->getFrameCount());
	QVERIFY(!testPlayer.getScrubbers().contains(testScrubber));
	QVERIFY(!testPlayer.controlsScrubber(*testScrubber));

	UIntegerInterval testInterval(4, 100); 
	testPlayer.setLoop(testInterval);
	testPlayer.addScrubber(testScrubber);
	QVERIFY(!testPlayer.isLooping());

	QEXPECT_EXCEPTION(testPlayer.addScrubber(testScrubber, 10), IllegalArgumentException);
}

void PlayerTest::initTestCase() {
	testContext = GlobalContext::get();
}

void PlayerTest::testDummy() {
	Saveable::sptr dummy = Player::getDummy();
	QVERIFY(dummy->isDummy());
}

void PlayerTest::saveRestore() {

        YUVDataVideo::sptr testVideo(new YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, YUVType::YUV444, testContext));
		VideoScrubber::sptr testScrubber(new VideoScrubber(testVideo));

        YUVDataVideo::sptr testVideo2(new YUVDataVideo("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, YUVType::YUV420, testContext));
		VideoScrubber::sptr testScrubber2(new VideoScrubber(testVideo2));

		Player testPlayer(10);

		testPlayer.addScrubber(testScrubber);
		testPlayer.addScrubber(testScrubber2);
		UIntegerInterval testInterval(5, 10);
		testPlayer.setLoop(testInterval);

		Memento memento = testPlayer.getMemento();
		Player::sptr dummy = Player::getDummy().dynamicCast<Player>();
		dummy->restore(memento);

		QCOMPARE(dummy->getFPS(), 10.0f);
		QCOMPARE(dummy->scrubberCount(), 2U);
		QVERIFY(dummy->controlsScrubber(*testScrubber));
		QVERIFY(dummy->controlsScrubber(*testScrubber2));
		QVERIFY(!dummy->isPlaying());
		QCOMPARE(dummy->getCurrentFrameNumber(), 5U);
		QVERIFY(dummy->isLooping());
		QCOMPARE(dummy->getLoop().getStart(), 5U);
		QCOMPARE(dummy->getLoop().getEnd(), 10U);

		testPlayer.jumpToFrameNr(7);
		testPlayer.removeScrubber(*testScrubber);
		testPlayer.restore(memento);
		QCOMPARE(testPlayer.getCurrentFrameNumber(), 7U);
		QVERIFY(testPlayer.controlsScrubber(*testScrubber));
		QCOMPARE(testPlayer.scrubberCount(), 2U);
}

}  // namespace player
}  // namespace model