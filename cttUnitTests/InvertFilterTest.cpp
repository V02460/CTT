#include "InvertFilterTest.h"

#include "CustomTestingMacros.h"

#include "InvertFilter.h"
#include "FilterParam.h"

using model::filter::InvertFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;

void InvertFilterTest::initTestCase() {
    testContext.reset(new QOpenGLContext());
    testContext->create();

    surface.create();

    testContext->makeCurrent(&surface);

    video.reset(new YUVDataVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv",
        QSize(720, 576),
        24,
        YUVType::YUV422,
        testContext));
}

void InvertFilterTest::testRun() {
    InvertFilter invertFilter(video);
    invertFilter.getFrame(13);
}

void InvertFilterTest::wrongParams() {
    InvertFilter invertFilter(video);
    QEXPECT_EXCEPTION(invertFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all"))),
                      IllegalArgumentException);
    QEXPECT_EXCEPTION(invertFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 3.05))),
                      IllegalArgumentException);
}