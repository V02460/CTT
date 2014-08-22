#include "FilteredVideoTest.h"

#include <QOffscreenSurface>
#include "CustomTestingMacros.h"
#include "YUVDataVideo.h"
#include "FilteredVideo.h"

#include "IllegalStateException.h"

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
	model::video::YUVDataVideo::sptr baseVideo(
        new model::video::YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv",
                                       QSize(720, 576),
                                       24,
                                       model::video::YUVType::YUV444,
                                       testContext));

	FilteredVideo testVideo(baseVideo);
}
