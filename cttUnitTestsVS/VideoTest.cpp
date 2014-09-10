#include <CppUnitTest.h>
#include <functional>

#include "YUVDataVideo.h"
#include "GlobalContext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using ::model::GlobalContext;

namespace ctt_unit_tests {
	TEST_CLASS(VideoTest) {
public:
	TEST_METHOD_INITIALIZE(initTestCase) {
		testContext = GlobalContext::get();
	}

	TEST_METHOD(test) {
		model::video::YUVDataVideo::sptr testVideo(new model::video::YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
		testVideo->getMetadata().getSize();
		testVideo->getResolution();
		model::video::Video::getScaledFrame(testVideo, 10, QSize(100, 100));
	}

private:
	QSharedPointer<QOpenGLContext> testContext;
	};
}