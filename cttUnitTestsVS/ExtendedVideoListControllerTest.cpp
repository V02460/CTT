#include <CppUnitTest.h>
#include <functional>

#include <QOffscreenSurface>

#include "YUVDataVideo.h"
#include "ExtendedVideoListController.h"
#include "FilteredVideo.h"
#include "GlobalContext.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using model::video::YUVDataVideo;
using model::filter::FilteredVideo;
using model::GlobalContext;
using controller::ExtendedVideoListController;
using model::filter::FilteredVideo;
using model::saveable::SaveableList;
using model::player::Player;
using model::video::YUVType;

namespace ctt_unit_tests {
	TEST_CLASS(ExtendedVideoListControllerTest) {
public:
	TEST_METHOD_INITIALIZE(initTestCase) {
		testContext = GlobalContext::get();

		video1.reset(new YUVDataVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv",
			QSize(720, 576),
			24,
			YUVType::YUV422,
			false,
			testContext));

		video2.reset(new YUVDataVideo("Resources/Videos/YUV420/raftingNEW_352x288_113.yuv",
			QSize(352, 288),
			24,
			YUVType::YUV420,
			false,
			testContext));
	}

	TEST_METHOD(testRun) {
		SaveableList<FilteredVideo>::sptr videoList1(new SaveableList<FilteredVideo>());
		SaveableList<FilteredVideo>::sptr videoList2(new SaveableList<FilteredVideo>());
		SaveableList<Player>::sptr playerList(new SaveableList<Player>());

		FilteredVideo::sptr filteredVideo(new FilteredVideo(video1));
		ExtendedVideoListController videoListController(videoList1, videoList2, playerList);

		videoListController.addVideo(filteredVideo);
		videoList1->getSize();
		videoList1->get(0)->getBaseVideo();

		videoListController.addVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv", 720, 576, 24, YUVType::YUV422, false);
		videoList1->getSize();
		
		videoListController.addVideo("Resources/Videos/YUV420/raftingNEW_352x288_113.yuv", "Resources/Videos/YUV420/ModeGrid_raf_512my.dat", 352, 288, 24, YUVType::YUV420, false);
		videoList1->getSize();

		videoListController.removeVideo(2);
		videoList1->getSize();

		videoListController.removeVideo(1);
		videoList1->getSize();
		videoList1->get(0)->getBaseVideo();

		videoListController.removeVideo(0);
		videoList1->getSize();
	}
private:
	QSharedPointer<QOpenGLContext> testContext;
	QOffscreenSurface surface;
	::model::video::YUVDataVideo::sptr video1;
	::model::video::YUVDataVideo::sptr video2;
	};
}