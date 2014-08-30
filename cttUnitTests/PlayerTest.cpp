#include "PlayerTest.h"
#include "..\CTT\YUVDataVideo.h"
#include "..\CTT\VideoScrubber.h"
#include "..\CTT\IllegalArgumentException.h"
#include "CustomTestingMacros.h"
#include "..\CTT\UIntegerInterval.h"

using model::video::YUVDataVideo;
using model::player::Player;
using model::player::VideoScrubber;
using exception::IllegalArgumentException;

void PlayerTest::emptyPlayer()
{
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

void PlayerTest::playingAndLooping()
{
	model::video::YUVDataVideo *testVideo = new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext);
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

	model::UIntegerInterval testInterval(5, 10);
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

	model::UIntegerInterval testInterval2(0, 14);
	testPlayer.setLoop(testInterval2);

	model::UIntegerInterval testInterval3(0, 100);
	QEXPECT_EXCEPTION(testPlayer.setLoop(testInterval3), IllegalArgumentException);
}

void PlayerTest::scrubberOperations()
{
	model::video::YUVDataVideo *testVideo = new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext);
	YUVDataVideo::sptr videoPointer(testVideo);
	VideoScrubber::sptr testScrubber(new VideoScrubber(videoPointer));

	model::video::YUVDataVideo *testVideo2 = new model::video::YUVDataVideo("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);
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

	model::UIntegerInterval testInterval(4, 100); 
	testPlayer.setLoop(testInterval);
	testPlayer.addScrubber(testScrubber);
	QVERIFY(!testPlayer.isLooping());

	QEXPECT_EXCEPTION(testPlayer.addScrubber(testScrubber, 10), IllegalArgumentException);
}

void PlayerTest::initTestCase()
{
	surface.create();
	testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
	testContext->create();
	QVERIFY2(testContext->makeCurrent(&surface), "Couldn't initialize OGL Context.");
}

void PlayerTest::testDummy()
{
	model::saveable::Saveable::sptr dummy = Player::getDummy();
	QVERIFY(dummy->isDummy());
}

void PlayerTest::saveRestore()
{

		model::video::YUVDataVideo *testVideo = new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext);
		YUVDataVideo::sptr videoPointer(testVideo);
		VideoScrubber::sptr testScrubber(new VideoScrubber(videoPointer));

		model::video::YUVDataVideo *testVideo2 = new model::video::YUVDataVideo("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);
		YUVDataVideo::sptr videoPointer2(testVideo2);
		VideoScrubber::sptr testScrubber2(new VideoScrubber(videoPointer2));

		Player testPlayer(10);

		testPlayer.addScrubber(testScrubber);
		testPlayer.addScrubber(testScrubber2);
		model::UIntegerInterval testInterval(5, 10);
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
