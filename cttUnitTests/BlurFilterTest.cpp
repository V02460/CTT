#include "BlurFilterTest.h"

#include "BlurFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"
#include "Memento.h"

using model::filter::BlurFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;
using model::saveable::Memento;
using exception::AccessToDummyException;

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
    QVERIFY_EXCEPTION_THROWN(blurFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all"))),
		                     IllegalArgumentException);
    QVERIFY_EXCEPTION_THROWN(blurFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 1.0))),
		                     IllegalArgumentException);
    blurFilter.getFrame(9);
}

void BlurFilterTest::memento() {
    BlurFilter testFilter(video);
    testFilter.setParam(FilterParam::sptr(new FilterParam(BlurFilter::kParamRadiusStr, 10.f)));

    Memento memento = testFilter.getMemento();

    BlurFilter::sptr dummyFilter = BlurFilter::getDummy().dynamicCast<BlurFilter>();
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getFrame(7), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getMemento(), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getUsesList(), AccessToDummyException);
    QVERIFY2(dummyFilter->isDummy(), "Dummy tells me it's no dummy.");

    dummyFilter->restore(memento);

    QVERIFY2(dummyFilter->getParamValue<float>(BlurFilter::kParamRadiusStr) == 10.f, "Blur radius was not restored.");

    dummyFilter->getFrame(6);
}