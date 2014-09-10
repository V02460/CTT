#include <CppUnitTest.h>
#include <functional>

#include <QOpenGLContext>

#include "VideoMetadata.h"
#include "YUVDataVideo.h"
#include "Frame.h"
#include "GlobalContext.h"
#include "MacroblockType.h"
#include "GlobalContext.h"

#include "OpenGLException.h"
#include "IllegalArgumentException.h"
#include "FileNotFoundException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using model::frame::Frame;
using model::frame::MacroblockType;
using model::video::YUVDataVideo;
using model::video::VideoMetadata;
using model::GlobalContext;
using model::saveable::Memento;
using exception::FileNotFoundException;

namespace ctt_unit_tests {
	TEST_CLASS(YUVDataVideoTest) {
public:
	TEST_METHOD_INITIALIZE(initTestCase) {
		testContext = GlobalContext::get();
	}

	TEST_METHOD(dummyTest) {
		YUVDataVideo::getDummy()->isDummy();
	}

	TEST_METHOD(test444) {
		YUVDataVideo testVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext);
		testVideo.getFrameCount();

		VideoMetadata metadata = testVideo.getMetadata();
		metadata.getLength();
		metadata.getFPS();
		metadata.getSize().width();
		metadata.getSize().height();

		Frame::sptr testframe = testVideo.getFrame(10);
		testframe->getSize().width();
		testframe->getSize().height();

		testframe->getMetadata().hasMbMotionvectors();
		testframe->getMetadata().hasMbType();

		testframe->getMetadata().getSize().width();
		testframe->getMetadata().getSize().height();

		Assert::ExpectException<IllegalArgumentException>([&]() {testVideo.getFrame(testVideo.getFrameCount()); });
	}

	TEST_METHOD(test422) {
		YUVDataVideo testVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, testContext);
		testVideo.getFrameCount();

		VideoMetadata metadata = testVideo.getMetadata();
		metadata.getLength();
		metadata.getFPS();
		metadata.getSize().width();
		metadata.getSize().height();

		Frame::sptr testframe = testVideo.getFrame(10);
		testframe->getSize().width();
		testframe->getSize().height();

		testframe->getMetadata().hasMbMotionvectors();
		testframe->getMetadata().hasMbType();

		testframe->getMetadata().getSize().width();
		testframe->getMetadata().getSize().height();

		Assert::ExpectException<IllegalArgumentException>([&]() {testVideo.getFrame(testVideo.getFrameCount()); });
	}

	TEST_METHOD(test420) {
		YUVDataVideo testVideo("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);
		testVideo.getFrameCount();

		VideoMetadata metadata = testVideo.getMetadata();
		metadata.getLength();
		metadata.getFPS();
		metadata.getSize().width();
		metadata.getSize().height();

		Frame::sptr testframe = testVideo.getFrame(10);
		testframe->getSize().width();
		testframe->getSize().height();

		testframe->getMetadata().hasMbMotionvectors();
		testframe->getMetadata().hasMbType();

		testframe->getMetadata().getSize().width();
		testframe->getMetadata().getSize().height();

		testframe->getMetadata().hasMbMotionvectors();
		testframe->getMetadata().hasMbType();

		Assert::ExpectException<IllegalArgumentException>([&]() {testVideo.getFrame(testVideo.getFrameCount()); });
	}

	TEST_METHOD(invalidConstruction) {
		Assert::ExpectException<FileNotFoundException>([&]() {YUVDataVideo atest("thisfiledoesntexist", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext); });
		Assert::ExpectException<IllegalArgumentException>([&]() {YUVDataVideo btestVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(719, 576), 24, model::video::YUVType::YUV422, testContext); });
		Assert::ExpectException<IllegalArgumentException>([&]() {YUVDataVideo ctestVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(719, 576), 24, model::video::YUVType::YUV420, testContext); });
		Assert::ExpectException<IllegalArgumentException>([&]() {YUVDataVideo dtestVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 575), 24, model::video::YUVType::YUV420, testContext); });
		Assert::ExpectException<IllegalArgumentException>([&]() {YUVDataVideo etestVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(920, 886), 24, model::video::YUVType::YUV444, testContext); });
		Assert::ExpectException<FileNotFoundException>([&]() {YUVDataVideo ftestVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", "thismetadatafiledoesntexist", QSize(720, 576), 24, model::video::YUVType::YUV422, testContext); });

		Assert::ExpectException<IllegalArgumentException>([&]() {YUVDataVideo testVideo2("resources/Videos/YUV420/raftingNEW_352x288_113.yuv", "resources/Videos/YUV420/ModeGrid_RD1_Rafting.dat", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext); });
	}

	TEST_METHOD(saveRestore) {
		YUVDataVideo testVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, testContext);
		Memento memento = testVideo.getMemento();

		YUVDataVideo::sptr dummy = YUVDataVideo::getDummy().dynamicCast<YUVDataVideo>();

		dummy->restore(memento);
		dummy->getFrameCount();

		VideoMetadata metadata = dummy->getMetadata();
		metadata.getLength();
		metadata.getFPS();
		metadata.getSize().width();
		metadata.getSize().height();

		dummy->getContext();

		dummy->getFrame(10);
		dummy->getFrame(14);
		dummy->getFrame(0);

		YUVDataVideo testVideo2("resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);
		testVideo2.restore(memento);

		VideoMetadata metadata2 = testVideo2.getMetadata();
		metadata2.getLength();
		metadata2.getFPS();
		metadata2.getSize().width();
		metadata2.getSize().height();

		testVideo2.getContext();

		testVideo2.getFrame(10);
		testVideo2.getFrame(14);
		testVideo2.getFrame(0);

		YUVDataVideo testVideo3("resources/Videos/YUV420/raftingNEW_352x288_113.yuv", "resources/Videos/YUV420/ModeGrid_raf_512my.dat", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);

		memento = testVideo3.getMemento();

		testVideo.restore(memento);
		Frame::sptr testFrame = testVideo.getFrame(0);
		testFrame->getMetadata().hasMbType();
		testFrame->getMetadata().getMbType()[0][0];
		testFrame->getMetadata().getMbType()[0][9];
		testFrame->getMetadata().getMbType()[0][21];
		testFrame->getMetadata().getMbType()[1][0];

		testFrame.reset();
		testFrame = testVideo.getFrame(testVideo.getFrameCount() - 1);
		testFrame->getMetadata().getMbType()[17][21];
	}

	TEST_METHOD(testMacroblockMetadata) {
		YUVDataVideo testVideo("resources/Videos/YUV420/raftingNEW_352x288_113.yuv", "resources/Videos/YUV420/ModeGrid_raf_512my.dat", QSize(352, 288), 24, model::video::YUVType::YUV420, testContext);

		Frame::sptr testFrame = testVideo.getFrame(0);
		testFrame->getMetadata().hasMbType();
		testFrame->getMetadata().getMbType()[0][0];
		testFrame->getMetadata().getMbType()[0][9];
		testFrame->getMetadata().getMbType()[0][21];
		testFrame->getMetadata().getMbType()[1][0];

		testFrame.reset();
		testFrame = testVideo.getFrame(testVideo.getFrameCount() - 1);
		testFrame->getMetadata().getMbType()[17][21];
	}
private:
	QSharedPointer<QOpenGLContext> testContext;
	};
}