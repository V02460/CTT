#include "RGBChannelFilterTest.h"

#include "CustomTestingMacros.h"

#include "RGBChannelFilter.h"
#include "FilterParam.h"

using model::filter::RGBChannelFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;

RGBChannelFilterTest::RGBChannelFilterTest() : testContext(), video() {
}

void RGBChannelFilterTest::initTestCase() {
    testContext.reset(new QOpenGLContext());
    testContext->create();

    surface.create();

    testContext->makeCurrent(&surface);

    video.reset(new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
        QSize(352, 288),
        24,
        YUVType::YUV420,
        testContext));
}

void RGBChannelFilterTest::testRun() {
    RGBChannelFilter rgbChannelFilter(video);
    rgbChannelFilter.getFrame(9);
}

void RGBChannelFilterTest::wrongParams() {
    RGBChannelFilter rgbChannelFilter(video);
	QEXPECT_EXCEPTION(rgbChannelFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all"))), IllegalArgumentException);
	QEXPECT_EXCEPTION(rgbChannelFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 1.0))), IllegalArgumentException);
	QEXPECT_EXCEPTION(rgbChannelFilter.setParam(FilterParam::sptr(new FilterParam(RGBChannelFilter::kParamRedStr, 7.f))), IllegalArgumentException);
    rgbChannelFilter.getFrame(9);
	rgbChannelFilter.setParam(FilterParam::sptr(new FilterParam(RGBChannelFilter::kParamRedStr, 20)));
    rgbChannelFilter.getFrame(5);
	rgbChannelFilter.setParam(FilterParam::sptr(new FilterParam(RGBChannelFilter::kParamGreenStr, -10)));
    rgbChannelFilter.getFrame(2);
	rgbChannelFilter.setParam(FilterParam::sptr(new FilterParam(RGBChannelFilter::kParamBlueStr, 300)));
    rgbChannelFilter.getFrame(3);
}