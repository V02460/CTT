#include "ExtendedVideoListControllerTest.h"

#include "CustomTestingMacros.h"
#include "ExtendedVideoListController.h"
#include "FilteredVideo.h"
#include "GlobalContext.h"

using model::video::YUVDataVideo;
using model::filter::FilteredVideo;
using model::GlobalContext;
using controller::ExtendedVideoListController;
using model::filter::FilteredVideo;
using model::saveable::SaveableList;
using model::player::Player;
using model::video::YUVType;

void ExtendedVideoListControllerTest::initTestCase() {
    testContext = GlobalContext::get();

	video1.reset(new YUVDataVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv",
		QSize(720, 576),
		24,
		YUVType::YUV422,
		testContext));

	video2.reset(new YUVDataVideo("Resources/Videos/YUV420/raftingNEW_352x288_113.yuv",
		QSize(352, 288),
		24,
		YUVType::YUV420,
		testContext));

}

void ExtendedVideoListControllerTest::testRun() {
	SaveableList<FilteredVideo>::sptr videoList1(new SaveableList<FilteredVideo>());
	SaveableList<FilteredVideo>::sptr videoList2(new SaveableList<FilteredVideo>());
	SaveableList<Player>::sptr playerList(new SaveableList<Player>());

	FilteredVideo::sptr filteredVideo(new FilteredVideo(video1));
	ExtendedVideoListController videoListController(videoList1, videoList2, playerList);

	videoListController.addVideo(filteredVideo);
	QVERIFY2(videoList1->getSize() == 1, "Wrong number of videos in the videoList.");
	QVERIFY2(videoList1->get(0)->getBaseVideo() == filteredVideo, "The video in the videoList is not equal to the video that has been added.");

	videoListController.addVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv", 720, 576, 24, YUVType::YUV422);
	QVERIFY2(videoList1->getSize() == 2, "Wrong number of videos in the videoList.");
	//QVERIFY2(videoList->get(1)->getBaseVideo() == video, "The video in the videoList is not equal to the video that has been added.");

	videoListController.addVideo("Resources/Videos/YUV420/raftingNEW_352x288_113.yuv","Resources/Videos/YUV420/ModeGrid_raf_512my.dat", 352, 288, 24, YUVType::YUV420);
	QVERIFY2(videoList1->getSize() == 3, "Wrong number of videos in the videoList.");

	videoListController.removeVideo(2);
	QVERIFY2(videoList1->getSize() == 2, "Wrong number of videos in the videoList.");

	videoListController.removeVideo(1);
	QVERIFY2(videoList1->getSize() == 1, "Wrong number of videos in the videoList.");
	QVERIFY2(videoList1->get(0)->getBaseVideo() == filteredVideo, "The video in the videoList is not equal to the video that has been added.");

	videoListController.removeVideo(0);
	QVERIFY2(videoList1->getSize() == 0, "Wrong number of videos in the videoList.");

}