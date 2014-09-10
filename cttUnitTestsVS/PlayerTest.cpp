#include <CppUnitTest.h>
#include <functional>

#include <QObject>

#include "Player.h"
#include "YUVDataVideo.h"
#include "VideoScrubber.h"
#include "UIntegerInterval.h"
#include "GlobalContext.h"
#include "Memento.h"
#include "IllegalArgumentException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using ::model::video::YUVDataVideo;
using ::model::GlobalContext;
using ::exception::IllegalArgumentException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::model::video::YUVType;
using ::model::player::Player;
using ::model::player::VideoScrubber;
using ::model::UIntegerInterval;

namespace ctt_unit_tests {
	TEST_CLASS(PlayerTest) {
public:
	TEST_METHOD_INITIALIZE(initTestCase) {
		testContext = GlobalContext::get();
	}

	TEST_METHOD(emptyPlayer) {
		Player test(10);

		test.isPlaying();
		test.isLooping();

		test.getScrubbers().isEmpty();

		test.hasNextFrame();
		test.hasPreviousFrame();

		test.scrubberCount();
		test.getVideoLength();
		test.getCurrentFrameNumber();

		test.getFPS();

		test.setFPS(20);
		test.getFPS();
	}

	TEST_METHOD(playingAndLooping) {
		YUVDataVideo *testVideo = new YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, YUVType::YUV444, testContext);
		YUVDataVideo::sptr videoPointer(testVideo);
		VideoScrubber::sptr testScrubber(new VideoScrubber(videoPointer));

		Player testPlayer(10);
		testPlayer.addScrubber(testScrubber);

		testPlayer.isPlaying();
		testPlayer.hasPreviousFrame();
		testPlayer.hasNextFrame();
		testPlayer.getCurrentFrameNumber();

		testPlayer.previousFrame();
		testPlayer.hasPreviousFrame();
		testPlayer.hasNextFrame();
		testPlayer.getCurrentFrameNumber();

		testPlayer.nextFrame();
		testPlayer.hasPreviousFrame();
		testPlayer.hasNextFrame();
		testPlayer.getCurrentFrameNumber();


		testPlayer.jumpToFrameNr(13);
		testPlayer.hasPreviousFrame();
		testPlayer.hasNextFrame();
		testPlayer.getCurrentFrameNumber();

		testPlayer.nextFrame();
		testPlayer.hasPreviousFrame();
		testPlayer.hasNextFrame();
		testPlayer.getCurrentFrameNumber();

		Assert::ExpectException<IllegalArgumentException>([&]() {testPlayer.jumpToFrameNr(100); });

		testPlayer.play();
		testPlayer.isPlaying();
		testPlayer.pause();
		testPlayer.isPlaying();
		testPlayer.togglePlayPause();
		testPlayer.isPlaying();
		testPlayer.togglePlayPause();
		testPlayer.isPlaying();

		// TODO: Do we want this feature in the player?

		// Stop playback when using nextFrame
		testPlayer.play();
		testPlayer.nextFrame();
		testPlayer.isPlaying();

		// Stop playback when using previousFrame
		testPlayer.play();
		testPlayer.previousFrame();
		testPlayer.isPlaying();

		UIntegerInterval testInterval(5, 10);
		testPlayer.isLooping();
		testPlayer.setLoop(testInterval);
		testPlayer.isLooping();
		testPlayer.getLoop().getStart();
		testPlayer.getLoop().getEnd();
		testPlayer.jumpToFrameNr(10);
		testPlayer.getCurrentFrameNumber();
		testPlayer.nextFrame();
		testPlayer.getCurrentFrameNumber();
		testPlayer.nextFrame();
		testPlayer.getCurrentFrameNumber();
		testPlayer.previousFrame();
		testPlayer.previousFrame();
		testPlayer.getCurrentFrameNumber();

		testPlayer.stopLooping();
		testPlayer.isLooping();
		testPlayer.nextFrame();
		testPlayer.getCurrentFrameNumber();

		UIntegerInterval testInterval2(0, 14);
		testPlayer.setLoop(testInterval2);

		UIntegerInterval testInterval3(0, 100);
		Assert::ExpectException<IllegalArgumentException>([&]() {testPlayer.setLoop(testInterval3); });
	}

	TEST_METHOD(scrubberOperations) {
		YUVDataVideo *testVideo = new YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, YUVType::YUV444, testContext);
		YUVDataVideo::sptr videoPointer(testVideo);
		VideoScrubber::sptr testScrubber(new VideoScrubber(videoPointer));

		YUVDataVideo *testVideo2 = new YUVDataVideo("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, YUVType::YUV420, testContext);
		YUVDataVideo::sptr videoPointer2(testVideo2);
		VideoScrubber::sptr testScrubber2(new VideoScrubber(videoPointer2));

		Player testPlayer(10);

		testPlayer.getScrubbers().isEmpty();

		testPlayer.addScrubber(testScrubber2);
		testPlayer.scrubberCount();
		testPlayer.getVideoLength(), videoPointer2->getFrameCount();
		testPlayer.getScrubbers().contains(testScrubber2);
		testPlayer.controlsScrubber(*testScrubber2);

		testPlayer.addScrubber(testScrubber);
		testPlayer.scrubberCount();
		testPlayer.getVideoLength(), videoPointer->getFrameCount();
		testPlayer.getScrubbers().contains(testScrubber);
		testPlayer.controlsScrubber(*testScrubber);

		testPlayer.removeScrubber(*testScrubber);
		testPlayer.scrubberCount();
		testPlayer.getVideoLength(), videoPointer2->getFrameCount();
		testPlayer.getScrubbers().contains(testScrubber);
		testPlayer.controlsScrubber(*testScrubber);

		testPlayer.addScrubber(testScrubber, 0U);
		testPlayer.scrubberCount();
		testPlayer.getVideoLength(), videoPointer->getFrameCount();
		testPlayer.getScrubbers().at(0);
		testPlayer.controlsScrubber(*testScrubber);

		testPlayer.removeScrubber(0);
		testPlayer.scrubberCount();
		testPlayer.getVideoLength(), videoPointer2->getFrameCount();
		testPlayer.getScrubbers().contains(testScrubber);
		testPlayer.controlsScrubber(*testScrubber);

		UIntegerInterval testInterval(4, 100);
		testPlayer.setLoop(testInterval);
		testPlayer.addScrubber(testScrubber);
		testPlayer.isLooping();

		Assert::ExpectException<IllegalArgumentException>([&]() {testPlayer.addScrubber(testScrubber, 10); });
	}

	TEST_METHOD(testDummy) {
		Saveable::sptr dummy = Player::getDummy();
		dummy->isDummy();
	}

	TEST_METHOD(saveRestore) {
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

		dummy->getFPS();
		dummy->scrubberCount();
		dummy->controlsScrubber(*testScrubber);
		dummy->controlsScrubber(*testScrubber2);
		dummy->isPlaying();
		dummy->getCurrentFrameNumber();
		dummy->isLooping();
		dummy->getLoop().getStart();
		dummy->getLoop().getEnd();

		testPlayer.jumpToFrameNr(7);
		testPlayer.removeScrubber(*testScrubber);
		testPlayer.restore(memento);
		testPlayer.getCurrentFrameNumber();
		testPlayer.controlsScrubber(*testScrubber);
		testPlayer.scrubberCount();
	}
private:
	QSharedPointer<QOpenGLContext> testContext;
	};
}