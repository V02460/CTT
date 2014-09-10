#include <CppUnitTest.h>
#include <functional>

#include "YUVDataVideo.h"
#include "GlobalContext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ctt_unit_tests {

using ::model::GlobalContext;

TEST_CLASS(FileVideoTest) {
public:
TEST_METHOD_INITIALIZE(initTestCase) {
	testContext = GlobalContext::get();
}

TEST_METHOD(test) {
	model::video::YUVDataVideo::sptr testVideo(new model::video::YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
	testVideo->getContext() == testContext;
	testVideo->getPath();
	testVideo->uses(*testVideo.data());
	testVideo->getUsesList().size();
	testVideo->getUsesList().at(0) == testVideo;
}
private:
	QSharedPointer<QOpenGLContext> testContext;
};
}