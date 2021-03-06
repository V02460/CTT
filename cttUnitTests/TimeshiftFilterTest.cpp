#include "TimeshiftFilterTest.h"

#include "CustomTestingMacros.h"

#include "TimeshiftFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"
#include "AccessToDummyException.h"

using model::filter::TimeshiftFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;
using model::saveable::Memento;
using exception::AccessToDummyException;

TimeshiftFilterTest::TimeshiftFilterTest() : testContext(), video() {
}

void TimeshiftFilterTest::initTestCase() {
    testContext = GlobalContext::get();

    video.reset(new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
        QSize(352, 288),
        24,
        YUVType::YUV420,
        testContext));
}

void TimeshiftFilterTest::testRun() {
    TimeshiftFilter timeshiftFilter(video);
    timeshiftFilter.getFrame(9);
}

void TimeshiftFilterTest::wrongParams() {
    TimeshiftFilter timeshiftFilter(video);
	QEXPECT_EXCEPTION(timeshiftFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all"))), IllegalArgumentException);
	QEXPECT_EXCEPTION(timeshiftFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 1.0))), IllegalArgumentException);
    timeshiftFilter.getFrame(9);
	timeshiftFilter.setParam(FilterParam::sptr(new FilterParam(TimeshiftFilter::kParamShiftStr, -2)));
    timeshiftFilter.getFrame(4);
	timeshiftFilter.setParam(FilterParam::sptr(new FilterParam(TimeshiftFilter::kParamShiftStr, 9)));
    timeshiftFilter.getFrame(2);
	timeshiftFilter.setParam(FilterParam::sptr(new FilterParam(TimeshiftFilter::kParamShiftStr, -100)));
    timeshiftFilter.getFrame(3);
	timeshiftFilter.setParam(FilterParam::sptr(new FilterParam(TimeshiftFilter::kParamShiftStr, 100)));
    timeshiftFilter.getFrame(3);
}

void TimeshiftFilterTest::memento() {
    TimeshiftFilter testFilter(video);
    testFilter.setParam(FilterParam::sptr(new FilterParam(TimeshiftFilter::kParamShiftStr, 2014)));

    Memento memento = testFilter.getMemento();

    TimeshiftFilter::sptr dummyFilter = TimeshiftFilter::getDummy().dynamicCast<TimeshiftFilter>();
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getFrame(7), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getMemento(), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getUsesList(), AccessToDummyException);
    QVERIFY2(dummyFilter->isDummy(), "Dummy tells me it's no dummy.");

    dummyFilter->restore(memento);

    QCOMPARE(dummyFilter->getParamValue<int>(TimeshiftFilter::kParamShiftStr), 2014);

    dummyFilter->getFrame(6);
}