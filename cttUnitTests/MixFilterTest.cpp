#include "MixFilterTest.h"

#include "CustomTestingMacros.h"

#include "MixFilter.h"
#include "FilterParam.h"

using model::filter::MixFilter;
using model::video::YUVDataVideo;
using model::filter::FilterParam;

MixFilterTest::MixFilterTest() : testContext(), video1(), video2() {
}

void MixFilterTest::initTestCase() {
    testContext.reset(new QOpenGLContext());
    testContext->create();

    surface.create();

    testContext->makeCurrent(&surface);

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
    YUVDataVideo video3("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
                        QSize(352, 288),
                        24,
                        YUVType::YUV420,
                        testContext);

    //TODO: macro not working
    QFAIL("Exception testing macro not working properly, so i put this here...");
    //QEXPECT_EXCEPTION(MixFilter(video1, YUVDataVideo::sptr(&video3)), IllegalArgumentException);
}