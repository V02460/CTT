#include <CppUnitTest.h>
#include <functional>

#include "VideoListController.h"
#include "GlobalContext.h"
#include "YUVDataVideo.h"
#include "FilteredVideo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using model::video::YUVDataVideo;
using model::filter::FilteredVideo;
using controller::VideoListController;
using model::GlobalContext;
using model::video::YUVType;

namespace ctt_unit_tests {
	TEST_CLASS(VideoListControllerTest) {
public:
	TEST_METHOD_INITIALIZE(initTestCase) {
		testContext = GlobalContext::get();

		video.reset(new YUVDataVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv",
			QSize(720, 576),
			24,
			YUVType::YUV422,
			testContext));
	}
	
	TEST_METHOD(testRun) {
		::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList(new ::model::saveable::SaveableList<::model::filter::FilteredVideo>());
		FilteredVideo::sptr filteredVideo(new FilteredVideo(video));
		VideoListController videoListController(videoList);

		videoListController.addVideo(filteredVideo);
		videoList->getSize();
		videoList->get(0)->getBaseVideo();

		videoListController.addVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv", 720, 576, 24, YUVType::YUV422);
		videoList->getSize();

		videoListController.removeVideo(1);
		videoList->getSize();
		videoList->get(0)->getBaseVideo();

		videoListController.removeVideo(0);
		videoList->getSize();
	}
private:
	QSharedPointer<QOpenGLContext> testContext;
	::model::video::YUVDataVideo::sptr video;
	};
}