#include "BlurFilterTest.h"

#include "BlurFilter.h"
#include "YUVDataVideo.h"

using model::filter::BlurFilter;
using model::video::YUVDataVideo;

BlurFilterTest::BlurFilterTest() {}
BlurFilterTest::~BlurFilterTest() {}

void BlurFilterTest::init() {
    testContext.reset(new QOpenGLContext());
    testContext->create();
}

void BlurFilterTest::testRun() {
    YUVDataVideo::sptr video(
        new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
                         QSize(352, 288),
                         24,
                         YUVType::YUV420,
                         testContext));

    BlurFilter blurFilter(video);
    blurFilter.getFrame(9);
}