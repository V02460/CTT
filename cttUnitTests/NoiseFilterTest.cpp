#include "NoiseFilterTest.h"

#include "CustomTestingMacros.h"

#include "NoiseFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"
#include "AccessToDummyException.h"

using model::filter::NoiseFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;
using model::saveable::Memento;
using exception::AccessToDummyException;

NoiseFilterTest::NoiseFilterTest() : testContext(), video() {
}

void NoiseFilterTest::initTestCase() {
    testContext = GlobalContext::get();

    video.reset(new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
        QSize(352, 288),
        24,
        YUVType::YUV420,
        testContext));
}

void NoiseFilterTest::testRun() {
    NoiseFilter noiseFilter(video);
    noiseFilter.getFrame(9);
}

void NoiseFilterTest::wrongParams() {
    NoiseFilter noiseFilter(video);
	QEXPECT_EXCEPTION(noiseFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all"))),
		              IllegalArgumentException);
	QEXPECT_EXCEPTION(noiseFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 1.0))),
		              IllegalArgumentException);
    noiseFilter.getFrame(9);
	noiseFilter.setParam(FilterParam::sptr(new FilterParam(NoiseFilter::kParamIntensityStr, 0.8f)));
    noiseFilter.getFrame(5);
	noiseFilter.setParam(FilterParam::sptr(new FilterParam(NoiseFilter::kParamIntensityStr, -10.f)));
    noiseFilter.getFrame(2);
	noiseFilter.setParam(FilterParam::sptr(new FilterParam(NoiseFilter::kParamIntensityStr, 42.f)));
    noiseFilter.getFrame(3);
}

void NoiseFilterTest::memento() {
    NoiseFilter testFilter(video);
    testFilter.setParam(FilterParam::sptr(new FilterParam(NoiseFilter::kParamIntensityStr, 0.8f)));

    Memento memento = testFilter.getMemento();

    NoiseFilter::sptr dummyFilter = NoiseFilter::getDummy().dynamicCast<NoiseFilter>();
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getFrame(7), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getMemento(), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getUsesList(), AccessToDummyException);
    QVERIFY2(dummyFilter->isDummy(), "Dummy tells me it's no dummy.");

    dummyFilter->restore(memento);

    QVERIFY2(dummyFilter->getParamValue<float>(NoiseFilter::kParamIntensityStr) == 0.8f, "Intensity was not restored.");

    dummyFilter->getFrame(6);
}