#include "BlurFilterTest.h"

#include "CustomTestingMacros.h"

#include "BlurFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"

using model::filter::BlurFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;

BlurFilterTest::BlurFilterTest() : testContext(), video() {
}

void BlurFilterTest::initTestCase() {
    testContext = GlobalContext::get();

    video.reset(new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
                                 QSize(352, 288),
                                 24,
                                 YUVType::YUV420,
                                 testContext));
}

void BlurFilterTest::testRun() {
    BlurFilter blurFilter(video);
    blurFilter.getFrame(9);
}

void BlurFilterTest::wrongParams() {
    BlurFilter blurFilter(video);
    QEXPECT_EXCEPTION(blurFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all"))),
		              IllegalArgumentException);
	QEXPECT_EXCEPTION(blurFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 1.0))),
		              IllegalArgumentException);
    blurFilter.getFrame(9);
}