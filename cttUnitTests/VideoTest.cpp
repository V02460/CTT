#include "VideoTest.h"

#include "CustomTestingMacros.h"
#include "YUVDataVideo.h"
#include "GlobalContext.h"

using ::model::GlobalContext;

void VideoTest::initTestCase()
{
    testContext = GlobalContext::get();
}

void VideoTest::test()
{
	model::video::YUVDataVideo::sptr testVideo(new model::video::YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
	QVERIFY(testVideo->getResolution() == testVideo->getMetadata().getSize());
	model::video::Video::getScaledFrame(testVideo, 10, QSize(100, 100));
	//TODO igzgf save
}
