#include "GreyscaleFilterTest.h"

#include "CustomTestingMacros.h"

#include "GreyscaleFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"

using model::filter::GreyscaleFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;

GreyscaleFilterTest::GreyscaleFilterTest() : testContext(), video() {
}

void GreyscaleFilterTest::initTestCase() {
    testContext = GlobalContext::get();

    video.reset(new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
        QSize(352, 288),
        24,
        YUVType::YUV420,
        testContext));
}

void GreyscaleFilterTest::testRun() {
    GreyscaleFilter greyscaleFilter(video);
    greyscaleFilter.getFrame(9);
}

void GreyscaleFilterTest::wrongParams() {
    GreyscaleFilter greyscaleFilter(video);
	QEXPECT_EXCEPTION(greyscaleFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all"))),
		              IllegalArgumentException);
	QEXPECT_EXCEPTION(greyscaleFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 1.0))),
		              IllegalArgumentException);
    greyscaleFilter.getFrame(9);
}