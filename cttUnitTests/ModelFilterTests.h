#ifndef _MODELFILTERTESTS_H
#define _MODELFILTERTESTS_H

#include "TestResult.h"

#include "FilterTest.h"
#include "BlurFilterTest.h"
#include "MixFilterTest.h"
#include "RescaleFilterTest.h"
#include "GreyscaleFilterTest.h"
#include "NoiseFilterTest.h"
#include "TimeshiftFilterTest.h"
#include "RGBChannelFilterTest.h"

#include "FilteredVideoTest.h"

namespace model {
namespace filter {

static TestResult test(int argc, char *argv[]) {
    TestResult r("filter");

    FilterTest filterTest;
    BlurFilterTest blurFilterTest;
    MixFilterTest mixFilterTest;
    RescaleFilterTest rescaleFilterTest;
    GreyscaleFilterTest greyscaleFilterTest;
    NoiseFilterTest noiseFilterTest;
    TimeshiftFilterTest timeshiftFilterTest;
    RGBChannelFilterTest rgbChannelFilterTest;

    FilteredVideoTest filteredVideoTest;

    r << TestResult("FilterTest", QTest::qExec(&filterTest, argc, argv))
      << TestResult("BlurFilterTest", QTest::qExec(&blurFilterTest, argc, argv))
      << TestResult("MixFilterTest", QTest::qExec(&mixFilterTest, argc, argv))
      << TestResult("RescaleFilterTest", QTest::qExec(&rescaleFilterTest, argc, argv))
      << TestResult("GreycaleFilterTest", QTest::qExec(&greyscaleFilterTest, argc, argv))
      << TestResult("NoiseFilterTest", QTest::qExec(&noiseFilterTest, argc, argv))
      << TestResult("TimeshiftFilterTest", QTest::qExec(&timeshiftFilterTest, argc, argv))
      << TestResult("RGBChannelFilterTest", QTest::qExec(&rgbChannelFilterTest, argc, argv))

      << TestResult("FilteredVideoTest", QTest::qExec(&filteredVideoTest, argc, argv));

    return r;
}

}  // namespace filter
}  // namespace model

#endif