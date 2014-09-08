#include "InvertFilterTest.h"

#include "CustomTestingMacros.h"

#include "InvertFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"
#include "AccessToDummyException.h"

using model::filter::InvertFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;
using model::saveable::Memento;
using exception::AccessToDummyException;

void InvertFilterTest::initTestCase() {
    testContext = GlobalContext::get();

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

void InvertFilterTest::memento() {
    InvertFilter testFilter(video);

    Memento memento = testFilter.getMemento();

    InvertFilter::sptr dummyFilter = InvertFilter::getDummy().dynamicCast<InvertFilter>();
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getFrame(7), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getMemento(), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getUsesList(), AccessToDummyException);
    QVERIFY2(dummyFilter->isDummy(), "Dummy tells me it's no dummy.");

    dummyFilter->restore(memento);
    dummyFilter->getFrame(6);
}