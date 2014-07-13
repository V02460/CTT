#include "VideoScrubberTest.h"
#include "..\ctt\VideoScrubber.h"
#include "..\ctt\IllegalStateException.h"
#include "CustomTestingMacros.h"
#include "BBBTestVideo.h"

void VideoScrubberTest::testDummy()
{
	QSharedPointer<model::saveable::Saveable> dummy = model::player::VideoScrubber::getDummy();

	QVERIFY2(dummy->isDummy(), "The generated dummy claimed not to be a dummy.");
}

void VideoScrubberTest::invalidConstruction()
{
	BBBTestVideo testVideo(10);
}

void VideoScrubberTest::methods()
{

}
