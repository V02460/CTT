#include "RescaleFilterTest.h"

#include "CustomTestingMacros.h"

#include "RescaleFilter.h"
#include "FilterParam.h"

using model::filter::RescaleFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;

RescaleFilterTest::RescaleFilterTest() : testContext(), video() {
}

void RescaleFilterTest::initTestCase() {
    testContext.reset(new QOpenGLContext());
    testContext->create();

    surface.create();

    testContext->makeCurrent(&surface);

    video.reset(new YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv",
        QSize(720, 576),
        24,
        YUVType::YUV444,
        testContext));
}

void RescaleFilterTest::testRun() {
    RescaleFilter rescaleFilter(video);
    rescaleFilter.getFrame(13);
}

void RescaleFilterTest::wrongParams() {
    RescaleFilter rescaleFilter(video);

    // some really wrong values
	QEXPECT_EXCEPTION(rescaleFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all"))), IllegalArgumentException);
	QEXPECT_EXCEPTION(rescaleFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 1.0))), IllegalArgumentException);
	QEXPECT_EXCEPTION(rescaleFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSize, "WRONG!"))), IllegalArgumentException);
    rescaleFilter.getFrame(9);

    // test a proper value
	rescaleFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSize, QSize(10, 500))));
    rescaleFilter.getFrame(14);

    // test some invalid values which should be handled silently by the class
	rescaleFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSize, QSize(200, 0))));
    rescaleFilter.getFrame(3);
	rescaleFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSize, QSize(-10, 5))));
    rescaleFilter.getFrame(3);
}