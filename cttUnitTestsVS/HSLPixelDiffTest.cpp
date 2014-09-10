#include <CppUnitTest.h>
#include <functional>

#include <QOpenGLContext>

#include "YUVDataVideo.h"
#include "HSLPixelDiff.h"
#include "GlobalContext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using model::video::YUVDataVideo;
using model::GlobalContext;
using model::video::YUVType;
using model::difference::HSLPixelDiff;

namespace ctt_unit_tests {
	TEST_CLASS(HSLPixelDiffTest) {
public:
	TEST_METHOD_INITIALIZE(initTestCase) {
		testContext = GlobalContext::get();

		video1.reset(new YUVDataVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv",
			QSize(720, 576),
			24,
			YUVType::YUV422,
			testContext));

		video2.reset(new YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv",
			QSize(720, 576),
			24,
			YUVType::YUV444,
			testContext));
	}

	TEST_METHOD(testRun) {
		HSLPixelDiff diff(video1, video2);
		diff.getDiff(5);
		diff.getPixelDiff(8);
	}

	TEST_METHOD(badArgs) {
		HSLPixelDiff diff(video1, video2);
		Assert::ExpectException<IllegalArgumentException>([&]() {diff.getDiff(-6); });
		Assert::ExpectException<IllegalArgumentException>([&]() {diff.getPixelDiff(666); });
	}

private:
	QSharedPointer<QOpenGLContext> testContext;
	::model::video::YUVDataVideo::sptr video1;
	::model::video::YUVDataVideo::sptr video2;
	};
}