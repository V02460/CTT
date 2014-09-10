#include "RescaleFilterTest.h"

#include "CustomTestingMacros.h"

#include "RescaleFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"
#include "AccessToDummyException.h"

using model::filter::RescaleFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;
using model::saveable::Memento;
using exception::AccessToDummyException;

RescaleFilterTest::RescaleFilterTest() : testContext(), video() {
}

void RescaleFilterTest::initTestCase() {
    testContext = GlobalContext::get();

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
	QEXPECT_EXCEPTION(rescaleFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSizeHeight, "WRONG!"))), IllegalArgumentException);
    rescaleFilter.getFrame(9);

    // test a proper value
	rescaleFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSizeWidth, 10U)));
    rescaleFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSizeHeight, 500U)));
    rescaleFilter.getFrame(14);

    // test some invalid values which should be handled silently by the class
	rescaleFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSizeHeight, 0U)));
    rescaleFilter.getFrame(3);
	rescaleFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSizeWidth, 0U)));
    rescaleFilter.getFrame(3);
}

void RescaleFilterTest::memento() {
    RescaleFilter testFilter(video);
    testFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSizeWidth, 314U)));
    testFilter.setParam(FilterParam::sptr(new FilterParam(RescaleFilter::kParamNewSizeHeight, 159U)));

    Memento memento = testFilter.getMemento();

    RescaleFilter::sptr dummyFilter = RescaleFilter::getDummy().dynamicCast<RescaleFilter>();
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getFrame(7), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getMemento(), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getUsesList(), AccessToDummyException);
    QVERIFY2(dummyFilter->isDummy(), "Dummy tells me it's no dummy.");

    dummyFilter->restore(memento);

    QCOMPARE(dummyFilter->getParamValue<unsigned int>(RescaleFilter::kParamNewSizeWidth), 314U);
    QCOMPARE(dummyFilter->getParamValue<unsigned int>(RescaleFilter::kParamNewSizeHeight), 159U);

    dummyFilter->getFrame(6);
}