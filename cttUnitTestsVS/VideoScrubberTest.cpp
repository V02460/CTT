#include <CppUnitTest.h>
#include <functional>

#include "VideoScrubber.h"
#include "YUVDataVideo.h"
#include "GlobalContext.h"

#include "IllegalStateException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using model::player::VideoScrubber;
using model::video::YUVDataVideo;
using model::GlobalContext;
using model::saveable::Saveable;
using model::video::YUVDataVideo;
using exception::IllegalArgumentException;
using model::saveable::Memento;

namespace ctt_unit_tests {
	TEST_CLASS(VideoScrubberTest) {
public:
	TEST_METHOD_INITIALIZE(initTestCase) {
		testContext = GlobalContext::get();
	}

	TEST_METHOD(testDummy) {
		Saveable::sptr dummy = VideoScrubber::getDummy();

		dummy->isDummy();
	}

	TEST_METHOD(methods) {
		YUVDataVideo::sptr testVideo(new YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
		VideoScrubber testScrubber(testVideo);

		testVideo->getMetadata().getSize();
		testScrubber.getVideoMetadata().getSize();

		testScrubber.getFrameCount(), testVideo->getFrameCount();

		testScrubber.getVideo();

		testScrubber.isWaitingForFrame();

		testScrubber.getCurrentFrame();
		testScrubber.jumpToFrameNr(10);
		testScrubber.getCurrentFrame();

		Assert::ExpectException<IllegalArgumentException>([&]() {testScrubber.jumpToFrameNr(testScrubber.getFrameCount()); });

		VideoScrubber testScrubber2(testVideo, 10);

		Assert::ExpectException<IllegalArgumentException>([&]() {VideoScrubber testScrubber3(testVideo, 20); });
	}

	TEST_METHOD(saveRestore) {
		YUVDataVideo::sptr testVideo(new YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
		VideoScrubber testScrubber(testVideo);

		Memento memento = testScrubber.getMemento();

		VideoScrubber::sptr dummy = VideoScrubber::getDummy().dynamicCast<VideoScrubber>();

		dummy->restore(memento);
		dummy->isDummy();
		dummy->getVideo();


		YUVDataVideo::sptr testVideo2(new YUVDataVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, testContext));
		VideoScrubber testScrubber2(testVideo2);

		testScrubber2.restore(memento);
		testScrubber2.getVideo();

		YUVDataVideo::sptr nullPointer;
		memento.setSharedPointer("video", nullPointer);
		Assert::ExpectException<IllegalArgumentException>([&]() {dummy->restore(memento); });
	}
private:
	QSharedPointer<QOpenGLContext> testContext;
	};
}