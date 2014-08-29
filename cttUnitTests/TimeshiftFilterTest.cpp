#include "TimeshiftFilterTest.h"

#include "CustomTestingMacros.h"

#include "TimeshiftFilter.h"
#include "FilterParam.h"

using model::filter::TimeshiftFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;

TimeshiftFilterTest::TimeshiftFilterTest() : testContext(), video() {
}

void TimeshiftFilterTest::initTestCase() {
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

void TimeshiftFilterTest::testRun() {
    TimeshiftFilter timeshiftFilter(video);
    timeshiftFilter.getFrame(9);
}

void TimeshiftFilterTest::wrongParams() {
    TimeshiftFilter timeshiftFilter(video);
    QEXPECT_EXCEPTION(timeshiftFilter.setParam(FilterParam("not right", "at all")), IllegalArgumentException);
    QEXPECT_EXCEPTION(timeshiftFilter.setParam(FilterParam("a bit off", 1.0)), IllegalArgumentException);
    timeshiftFilter.getFrame(9);
    timeshiftFilter.setParam(FilterParam(TimeshiftFilter::kParamShiftStr, -2));
    timeshiftFilter.getFrame(4);
    timeshiftFilter.setParam(FilterParam(TimeshiftFilter::kParamShiftStr, 9));
    timeshiftFilter.getFrame(2);
    timeshiftFilter.setParam(FilterParam(TimeshiftFilter::kParamShiftStr, -100));
    timeshiftFilter.getFrame(3);
    timeshiftFilter.setParam(FilterParam(TimeshiftFilter::kParamShiftStr, 100));
    timeshiftFilter.getFrame(3);
}