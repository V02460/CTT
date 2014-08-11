#include "VideoScrubberTest.h"
#include "..\ctt\VideoScrubber.h"
#include "..\ctt\IllegalStateException.h"
#include "CustomTestingMacros.h"
#include "..\CTT\YUVDataVideo.h"

using model::player::VideoScrubber;
using exception::IllegalArgumentException;
using model::video::YUVDataVideo;

void VideoScrubberTest::testDummy()
{
 	QSharedPointer<model::saveable::Saveable> dummy = VideoScrubber::getDummy();
// 
// 	QVERIFY2(dummy->isDummy(), "The generated dummy claimed not to be a dummy.");
}

void VideoScrubberTest::invalidConstruction()
{
// 	model::video::YUVDataVideo testVideo = *dynamic_cast<model::video::YUVDataVideo*>(&(*model::video::YUVDataVideo::getDummy()));
// 
// 	QEXPECT_EXCEPTION(QSharedPointer<YUVDataVideo>(testVideo), IllegalArgumentException);	
}

void VideoScrubberTest::methods()
{

}
