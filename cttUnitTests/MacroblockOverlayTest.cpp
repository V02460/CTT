#include "MacroblockOverlayTest.h"

#include "CustomTestingMacros.h"

#include "MacroblockOverlay.h"
#include "FilterParam.h"

#include "IllegalStateException.h"

using model::filter::overlay::MacroblockOverlay;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using exception::IllegalStateException;

MacroblockOverlayTest::MacroblockOverlayTest() : testContext(), video() {
}

void MacroblockOverlayTest::initTestCase() {
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

void MacroblockOverlayTest::noMetadata() {
    MacroblockOverlay macroblockOverlay(video);
    QEXPECT_EXCEPTION(macroblockOverlay.getFrame(9), IllegalStateException);
}

// void MacroblockOverlayTest::wrongParams() {
//     MacroblockOverlay macroblockOverlay(video);
//     QEXPECT_EXCEPTION(macroblockOverlay.setParam(FilterParam("not right", "at all")), IllegalArgumentException);
//     QEXPECT_EXCEPTION(macroblockOverlay.setParam(FilterParam("a bit off", 1.0)), IllegalArgumentException);
//     macroblockOverlay.getFrame(9);
// }