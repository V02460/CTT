#include "VideoListControllerTest.h"
#include "CustomTestingMacros.h"
#include "VideoListController.h"
#include "GlobalContext.h"

#include "FilteredVideo.h"

using model::video::YUVDataVideo;
using model::filter::FilteredVideo;
using controller::VideoListController;
using model::GlobalContext;

void VideoListControllerTest::initTestCase() {
	testContext = GlobalContext::get();

    video.reset(new YUVDataVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv",
        QSize(720, 576),
        24,
        YUVType::YUV422,
        testContext));

}

void VideoListControllerTest::testRun() {
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList(new ::model::saveable::SaveableList<::model::filter::FilteredVideo>());
	initTestCase();
	FilteredVideo::sptr filteredVideo(new FilteredVideo(video));	
	VideoListController videoListController(videoList);

	videoListController.addVideo(filteredVideo);
	QVERIFY2(videoList->getSize() == 1, "Wrong number of videos in the videoList.");
	QVERIFY2(videoList->get(0)->getBaseVideo() == filteredVideo, "The video in the videoList is not equal to the video that has been added.");
	
	videoListController.addVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv", 720, 576, 24, YUVType::YUV422);
	QVERIFY2(videoList->getSize() == 2, "Wrong number of videos in the videoList.");
	//QVERIFY2(videoList->get(1)->getBaseVideo() == video, "The video in the videoList is not equal to the video that has been added.");
	
	videoListController.removeVideo(1);
	QVERIFY2(videoList->getSize() == 1, "Wrong number of videos in the videoList.");
	QVERIFY2(videoList->get(0)->getBaseVideo() == filteredVideo, "The video in the videoList is not equal to the video that has been added.");

	videoListController.removeVideo(0);
	QVERIFY2(videoList->getSize() == 0, "Wrong number of videos in the videoList.");

}