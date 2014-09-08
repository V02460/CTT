#include "RGBChannelFilterTest.h"

#include "CustomTestingMacros.h"

#include "RGBChannelFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"

using model::filter::RGBChannelFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;
using model::saveable::Memento;
using exception::AccessToDummyException;

RGBChannelFilterTest::RGBChannelFilterTest() : testContext(), video() {
}

void RGBChannelFilterTest::initTestCase() {
    testContext = GlobalContext::get();

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

void RGBChannelFilterTest::memento() {
    RGBChannelFilter testFilter(video);
    testFilter.setParam(FilterParam::sptr(new FilterParam(RGBChannelFilter::kParamRedStr, 99)));
    testFilter.setParam(FilterParam::sptr(new FilterParam(RGBChannelFilter::kParamGreenStr, 101)));
    testFilter.setParam(FilterParam::sptr(new FilterParam(RGBChannelFilter::kParamBlueStr, -1)));

    Memento memento = testFilter.getMemento();

    RGBChannelFilter::sptr dummyFilter = RGBChannelFilter::getDummy().dynamicCast<RGBChannelFilter>();
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getFrame(7), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getMemento(), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getUsesList(), AccessToDummyException);
    QVERIFY2(dummyFilter->isDummy(), "Dummy tells me it's no dummy.");

    dummyFilter->restore(memento);

    QCOMPARE(dummyFilter->getParamValue<int>(RGBChannelFilter::kParamRedStr), 99);
    QCOMPARE(dummyFilter->getParamValue<int>(RGBChannelFilter::kParamGreenStr), 101);
    QCOMPARE(dummyFilter->getParamValue<int>(RGBChannelFilter::kParamBlueStr), -1);

    dummyFilter->getFrame(6);
}