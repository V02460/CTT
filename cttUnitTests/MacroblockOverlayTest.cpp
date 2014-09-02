#include "MacroblockOverlayTest.h"

#include "CustomTestingMacros.h"

#include "MacroblockOverlay.h"
#include "FilterParam.h"
#include "GlobalContext.h"

#include "IllegalStateException.h"

using model::filter::overlay::MacroblockOverlay;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using exception::IllegalStateException;

MacroblockOverlayTest::MacroblockOverlayTest() : testContext(), video() {
}

void MacroblockOverlayTest::initTestCase() {
    testContext = GlobalContext::get();

    video.reset(new YUVDataVideo("Resources/Videos/YUV420/raftingNEW_352x288_113.yuv",
                                 "Resources/Videos/YUV420/ModeGrid_raf_512my.dat",
                                 QSize(352, 288),
                                 24,
                                 YUVType::YUV420,
                                 testContext));

    noMetadataVideo.reset(new YUVDataVideo("Resources/Videos/YUV420/waterfall_cif_420_352x288_260frames.yuv",
                                           QSize(352, 288),
                                           24,
                                           YUVType::YUV420,
                                           testContext));
}

void MacroblockOverlayTest::testRun() {
    MacroblockOverlay macroblockOverlay(video);
    macroblockOverlay.getFrame(7);
}

void MacroblockOverlayTest::noMetadata() {
    MacroblockOverlay macroblockOverlay(noMetadataVideo);
    QEXPECT_EXCEPTION(macroblockOverlay.getFrame(9), IllegalStateException);
}