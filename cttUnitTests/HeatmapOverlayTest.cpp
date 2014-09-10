#include "HeatmapOverlayTest.h"

#include "CustomTestingMacros.h"

#include "HeatmapOverlay.h"
#include "FilterParam.h"
#include "GlobalContext.h"
#include "YUVPixelDiff.h"
#include "NoiseFilter.h"

#include "IllegalStateException.h"

using model::filter::overlay::HeatmapOverlay;
using model::video::YUVDataVideo;
using model::filter::FilterParam;
using model::GlobalContext;
using model::video::YUVType;
using model::difference::YUVPixelDiff;
using model::difference::PixelDiff;
using model::filter::NoiseFilter;
using exception::IllegalStateException;

void HeatmapOverlayTest::initTestCase() {
    testContext = GlobalContext::get();

    video1.reset(new YUVDataVideo("Resources/Videos/YUV420/raftingNEW_352x288_113.yuv",
                                  "Resources/Videos/YUV420/ModeGrid_raf_512my.dat",
                                  QSize(352, 288),
                                  24,
                                  YUVType::YUV420,
                                  testContext));

    video2.reset(new NoiseFilter(video1));
}

void HeatmapOverlayTest::testRun() {
    HeatmapOverlay heatmapOverlay(video1, PixelDiff::sptr(new YUVPixelDiff(video1, video2)));
    heatmapOverlay.getFrame(7);
}