#include <CppUnitTest.h>
#include <functional>

#include <QObject>

#include "YUVDataVideo.h"
#include "MacroblockOverlay.h"
#include "FilterParam.h"
#include "GlobalContext.h"

#include "IllegalStateException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using model::filter::overlay::MacroblockOverlay;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;
using exception::IllegalStateException;

namespace ctt_unit_tests {
	TEST_CLASS(MacroblockOverlayTest) {
public:
	TEST_METHOD_INITIALIZE(initTestCase) {
		testContext = GlobalContext::get();

		video.reset(new YUVDataVideo("Resources/Videos/YUV420/raftingNEW_352x288_113.yuv",
			"Resources/Videos/YUV420/ModeGrid_raf_512my.dat",
			QSize(352, 288),
			24,
			YUVType::YUV420,
			testContext));

		noMetadataVideo.reset(new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
			QSize(352, 288),
			24,
			YUVType::YUV420,
			testContext));
	}

	TEST_METHOD(testRun) {
		MacroblockOverlay macroblockOverlay(video);
		macroblockOverlay.getFrame(7);
	}

	TEST_METHOD(noMetadata) {
		MacroblockOverlay macroblockOverlay(noMetadataVideo);
		Assert::ExpectException<IllegalStateException>([&]() {macroblockOverlay.getFrame(9);});
	}

private:
	QSharedPointer<QOpenGLContext> testContext;
	::model::video::YUVDataVideo::sptr video;
	::model::video::YUVDataVideo::sptr noMetadataVideo;
	};
}