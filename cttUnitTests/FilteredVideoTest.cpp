#include "FilteredVideoTest.h"
#include "..\ctt\IllegalStateException.h"
#include "CustomTestingMacros.h"
#include "..\CTT\YUVDataVideo.h"
#include "..\CTT\FilteredVideo.h"
#include "qoffscreensurface.h"

using exception::IllegalArgumentException;
using model::video::YUVDataVideo;
using model::filter::FilteredVideo;


void FilteredVideoTest::initTestCase()
{
	surface.create();

	testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
	testContext->create();
	QVERIFY2(testContext->makeCurrent(&surface), "Couldn't initialize OGL Context.");
}

void FilteredVideoTest::dummyTest()
{
	model::saveable::Saveable::sptr dummy = FilteredVideo::getDummy();
	QVERIFY(dummy->isDummy());
}

void FilteredVideoTest::filterOperations()
{
	model::video::YUVDataVideo::sptr baseVideo(new model::video::YUVDataVideo("C:/Users/Jonas/Source/Repos/CTT/x64/Debug/testresources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, testContext));
	FilteredVideo testVideo(baseVideo);
}
