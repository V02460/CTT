#include "MixFilterTest.h"

#include "CustomTestingMacros.h"

#include "MixFilter.h"
#include "FilterParam.h"
#include "GlobalContext.h"
#include "AccessToDummyException.h"

using model::filter::MixFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;
using model::saveable::Memento;
using exception::AccessToDummyException;

MixFilterTest::MixFilterTest() : testContext(), video1(), video2() {
}

void MixFilterTest::initTestCase() {
    testContext = GlobalContext::get();

    video1.reset(new YUVDataVideo("Resources/Videos/YUV422/squirrel-720x576-422P.yuv",
        QSize(720, 576),
        24,
        YUVType::YUV422,
        testContext));

    video2.reset(new YUVDataVideo("Resources/Videos/YUV444/squirrel-720x576-444P.yuv",
        QSize(720, 576),
        24,
        YUVType::YUV444,
        testContext));
}

void MixFilterTest::testRun() {
    MixFilter mixFilter(video1, video2);
    mixFilter.getFrame(13);
}

void MixFilterTest::wrongParams() {
    MixFilter mixFilter(video1, video2);
	QEXPECT_EXCEPTION(mixFilter.setParam(FilterParam::sptr(new FilterParam("not right", "at all"))),
		              IllegalArgumentException);
	QEXPECT_EXCEPTION(mixFilter.setParam(FilterParam::sptr(new FilterParam("a bit off", 1.0))),
		              IllegalArgumentException);
	QEXPECT_EXCEPTION(mixFilter.setParam(FilterParam::sptr(new FilterParam(MixFilter::kParamMixRatioStr, "WRONG!"))),
		              IllegalArgumentException);
    mixFilter.getFrame(9);
	mixFilter.setParam(FilterParam::sptr(new FilterParam(MixFilter::kParamMixRatioStr, 10.0f)));
    mixFilter.getFrame(14);
	mixFilter.setParam(FilterParam::sptr(new FilterParam(MixFilter::kParamMixRatioStr, -3.5f)));
    mixFilter.getFrame(3);
}

void MixFilterTest::differentSize() {
    YUVDataVideo::sptr video3(
        new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
                         QSize(352, 288),
                         24,
                         YUVType::YUV420,
                         testContext));

    //TODO: macro not working
    //QFAIL("Exception testing macro not working properly, so i put this here...");
    QEXPECT_EXCEPTION(MixFilter(video1, video3), IllegalArgumentException);
}

void MixFilterTest::memento() {
    MixFilter testFilter(video1, video2);
    testFilter.setParam(FilterParam::sptr(new FilterParam(MixFilter::kParamMixRatioStr, 0.314f)));

    Memento memento = testFilter.getMemento();

    MixFilter::sptr dummyFilter = MixFilter::getDummy().dynamicCast<MixFilter>();
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getFrame(7), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getMemento(), AccessToDummyException);
    QVERIFY_EXCEPTION_THROWN(dummyFilter->getUsesList(), AccessToDummyException);
    QVERIFY2(dummyFilter->isDummy(), "Dummy tells me it's no dummy.");

    dummyFilter->restore(memento);

    QCOMPARE(dummyFilter->getParamValue<float>(MixFilter::kParamMixRatioStr), 0.314f);

    dummyFilter->getFrame(6);
}